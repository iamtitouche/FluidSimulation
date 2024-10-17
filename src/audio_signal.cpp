#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <sstream>

#pragma pack(push, 1)

struct RIFFHeader {
    char chunkID[4];      // Should always be "RIFF"
    uint32_t chunkSize;
    char format[4];       // Should always be "WAVE"
};

// Structure pour le chunk "fmt "
struct FMTChunk {
    char subchunk1ID[4];  // Should be "fmt "
    uint32_t subchunk1Size;
    uint16_t audioFormat; // Format audio (1 pour PCM)
    uint16_t numChannels; // Nombre de canaux
    uint32_t sampleRate;  // Fréquence d'échantillonnage
    uint32_t byteRate;    // Nombre d'octets par seconde
    uint16_t blockAlign;  // Nombre d'octets par échantillon (nombre de canaux * bits par échantillon / 8)
    uint16_t bitsPerSample; // Bits par échantillon
};

// Structure pour le chunk "data"
struct DataChunk {
    char subchunk2ID[64]; // Should be  "data"
    uint32_t subchunk2Size;
    char o1[512];


    // Les données audio suivent ici, mais nous les lirons séparément
};

class data_WAVE {

    RIFFHeader header;
    FMTChunk fmt_chunk;
    DataChunk data_chunk;

    std::vector<std::vector<uint16_t>> samples;

    public:
        data_WAVE(const std::string& filename) {

            std::ifstream file(filename, std::ios::binary);
            if (!file.is_open()) {
                std::cerr << "Error: File cannot be opened" << std::endl;
            }

            // Reading RIFF header
            file.read(reinterpret_cast<char*>(&header), sizeof(RIFFHeader));
            if (std::string(header.chunkID, 4) != "RIFF" || std::string(header.format, 4) != "WAVE") {
                std::cerr << "Error: This file is not a valid WAV file." << std::endl;
            }

            // Reading FMT chunk
            file.read(reinterpret_cast<char*>(&fmt_chunk), sizeof(FMTChunk));
            if (std::string(fmt_chunk.subchunk1ID, 4) != "fmt ") {
                std::cerr << "Error: Chunk 'fmt ' not found." << std::endl;
            }

            // Reading DATA chunk
            file.read(reinterpret_cast<char*>(&data_chunk), sizeof(DataChunk));
            //if (std::string(data_chunk.subchunk2ID, 4) != "data") {
            //    std::cerr << "Error: 'data' chunk not found." << std::endl;
            //    return;
            //}

            samples.resize(fmt_chunk.numChannels, std::vector<uint16_t>(get_samples_per_channel()));

            read_samples(file);

            file.close();
        }

        std::string to_string() const {
            std::ostringstream oss;

            oss << "RIFF Header:" << std::endl;
            oss << "  Chunk ID: " << std::string(header.chunkID, 4) << std::endl;
            oss << "  Chunk Size: " << header.chunkSize << std::endl;
            oss << "  Format: " << std::string(header.format, 4) << std::endl;

            oss << "FMT Chunk:" << std::endl;
            oss << "  Subchunk1 ID: " << std::string(fmt_chunk.subchunk1ID, 4) << std::endl;
            oss << "  Subchunk1 Size: " << fmt_chunk.subchunk1Size << std::endl;
            oss << "  Audio Format: " << fmt_chunk.audioFormat << std::endl;
            oss << "  Number of Channels: " << fmt_chunk.numChannels << std::endl;
            oss << "  Sample Rate: " << fmt_chunk.sampleRate << std::endl;
            oss << "  Byte Rate: " << fmt_chunk.byteRate << std::endl;
            oss << "  Block Align: " << fmt_chunk.blockAlign << std::endl;
            oss << "  Bits per Sample: " << fmt_chunk.bitsPerSample << std::endl;

            oss << "Data Chunk:" << std::endl;
            oss << "  Subchunk2 ID: " <<std::string(data_chunk.subchunk2ID) << std::endl;
            oss << "  Subchunk2 Size: " << data_chunk.subchunk2Size << std::endl;
            oss << "  o1:" << std::string(data_chunk.o1, 512) << std::endl;


            return oss.str();
        }



        int get_samples_per_channel() {
            return data_chunk.subchunk2Size / fmt_chunk.blockAlign;
        }


        void read_samples(std::ifstream& file) {
            file.seekg(sizeof(RIFFHeader) + sizeof(FMTChunk) + sizeof(DataChunk), std::ios::beg);

            std::vector<uint16_t> raw_data(get_samples_per_channel() * fmt_chunk.numChannels);
            file.read(reinterpret_cast<char*>(raw_data.data()), data_chunk.subchunk2Size);

            // Distributing samples between the channels
            for (size_t i = 0; i < get_samples_per_channel(); i++) {
                for (size_t j = 0; j < fmt_chunk.numChannels; j++) {
                    samples[j][i] = raw_data[i * fmt_chunk.numChannels + j];
                }
            }
        }

};

int main2() {
    data_WAVE wave("../audiofiles/audio.wav");

    std::cout << wave.to_string() << std::endl;
    return EXIT_SUCCESS;
}

