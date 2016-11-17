// Sha1.cpp
// Task/Utilities
// CIS 22C F2016: Matthew Tso

#include "Sha1.h"

// Bit rotation macros
#define ROL8(num, shift)   ( (num << shift) | (num >> ( 8 - shift)) )
#define ROL64(num, shift)  ( (num << shift) | (num >> (64 - shift)) )
#define ROL32(num, shift)  ( (num << shift) | (num >> (32 - shift)) )
#define ROR32(num, shift)  ( (num >> shift) | (num << (32 - shift)) )

const int CHUNKCH_SIZE = 64; // 64 unsigned char in one 512 bit chunk
const int CHUNKUL_SIZE = 16; // 16 uint32 in one 512 bit chunk
const int CHUNKXT_SIZE = 80; // 80 uint32 'words' in the extended block of the main loop

// Initial magic constants (from FIPS180)
const uint32_t STATE_INIT[5] = {
    0x67452301,
    0xEFCDAB89,
    0x98BADCFE,
    0x10325476,
    0xC3D2E1F0
};

// Returns the hex character representation of an unsigned char.
char toHex(unsigned char& ch) {
    switch (ch) {
        case 0x0: return '0';
        case 0x1: return '1';
        case 0x2: return '2';
        case 0x3: return '3';
        case 0x4: return '4';
        case 0x5: return '5';
        case 0x6: return '6';
        case 0x7: return '7';
        case 0x8: return '8';
        case 0x9: return '9';
        case 0xA: return 'a';
        case 0xB: return 'b';
        case 0xC: return 'c';
        case 0xD: return 'd';
        case 0xE: return 'e';
        case 0xF: return 'f';

        default: throw "Not a hex char";
    }
}

void loopChunkInto(uint32_t* state, uint32_t* chunk_in)
{
	uint32_t chunk_xt[CHUNKXT_SIZE] = { 0 };

	// MARK: 9: Put chunk 16 into transformation chunk of 80
	for (int i = 0; i < CHUNKUL_SIZE; i++) {
		chunk_xt[i] = chunk_in[i];
	}

	for (int i = 16; i < CHUNKXT_SIZE; i++) {
		// 9.1: XOR
		uint32_t word1 = chunk_xt[i - 3];
		uint32_t word2 = chunk_xt[i - 8];
		uint32_t word3 = chunk_xt[i - 14];
		uint32_t word4 = chunk_xt[i - 16];
		uint32_t xorResult = (((word1 ^ word2) ^ word3) ^ word4);

		// 9.2: Left rotate
		chunk_xt[i] = ROL32(xorResult, 1);
	}

	// MARK: 10: Initialize variables with the hash's state before this chunk is looped
	uint32_t A = state[0];
	uint32_t B = state[1];
	uint32_t C = state[2];
	uint32_t D = state[3];
	uint32_t E = state[4];

	// MARK: 11: The main loop
	for (int i = 0; i < CHUNKXT_SIZE; i++) {
		uint32_t f;
		uint32_t k;

		// 11.1
		if (i >= 0 && i <= 19) {
			f = (B & C) | (~B & D); // Bit NOT is different from Bool NOT
			k = 0x5A827999;
		}
		else if (i >= 20 && i <= 39) {
			f = (B ^ C) ^ D;
			k = 0x6ED9EBA1;
		}
		else if (i >= 40 && i <= 59) {
			f = (B & C) | (B & D) | (C & D);
			k = 0x8F1BBCDC;
		}
		else if (i >= 60 && i <= 79) {
			f = (B ^ C) ^ D;
			k = 0xCA62C1D6;
		}

		// 11.2
		uint32_t temp = (ROL32(A, 5) + f + E + k + chunk_xt[i]);
		E = D;
		D = C;
		C = ROL32(B, 30);
		B = A;
		A = temp;
	}

	// MARK: 12: Add back into state
	state[0] += A;
	state[1] += B;
	state[2] += C;
	state[3] += D;
	state[4] += E;
}

string task::sha_1(const string& input) {

	// Initialize state variables from SHA-1's constants
	uint32_t state[5];
	for (int i = 0; i < 5; i++) {
		state[i] = STATE_INIT[i];
	}

	int input_length = (int)input.length(); // Cast the uint into an int
	int chunk_count = input_length / 64 + 1;

	// The chunk that the extra 1 bit gets put into
	// also the last chunk with the message bits in it
	int chunk_1bit = chunk_count - 1; 

	// If (message input_length) % 64 is greater than 55 (448%512 bits),
	// need to add another chunk for the 64 bits of message input_length
	// binary that needs to be added to the last chunk.
	if (input_length % 64 > 55) {
		chunk_count += 1;
	}

	// Allocate enough blocks for input input_length
	unsigned char** chunks_ch = new unsigned char*[chunk_count];
	uint32_t** chunks = new uint32_t*[chunk_count];

	for (int i = 0; i < chunk_count; i++) {
		// Blocks to catch the bits from the string input char-by-char
		chunks_ch[i] = new unsigned char[CHUNKCH_SIZE];

		// Blocks of uint32 'words' that will be used in the main loop
		chunks[i] = new uint32_t[CHUNKUL_SIZE];
	}

	// Zero blocks
	for (int i = 0; i < chunk_count; ++i) {
		for (int ch = 0; ch < CHUNKCH_SIZE; ch++) {
			chunks_ch[i][ch] = 0;
		}
		for (int ul = 0; ul < CHUNKUL_SIZE; ul++) {
			chunks[i][ul] = 0;
		}
	}

	// Append characters of input into char chunks
	for (int chunkIndex = 0; chunkIndex < chunk_count; ++chunkIndex) {
		for (int i = 0; i < CHUNKCH_SIZE && (i + chunkIndex * CHUNKCH_SIZE) < input_length; ++i) {
			chunks_ch[chunkIndex][i] = input[chunkIndex * CHUNKCH_SIZE + i];
		}
	}

	// Append 1 bit after the input bits
	chunks_ch[chunk_1bit][input_length % 64] = 1 << 7;

	// MARK: 6.1: Append original length of original input represented by 64 bits
	// Multiply string input_length by character bit size
	uint64_t input_length_64 = (input.length() * 8);
	// Mask off by character and shift bits left by 8
	for (int i = 1; i <= 8; i++) {
		chunks_ch[chunk_count - 1][CHUNKCH_SIZE - i] = (input_length_64)& 0xFF;
		input_length_64 >>= 8;
	}

	// For each uint32 chunk
	for (int i = 0; i < chunk_count; ++i) {
		// Convert 64char chunk into uint32 words
		for (int ui = 0; ui < CHUNKUL_SIZE; ++ui) {

			for (int ch = 0; ch < 4; ++ch) {
				// Bit OR combine the 8 bit char into the 32 bit uint
				chunks[i][ui] = chunks[i][ui] | chunks_ch[i][ui * 4 + ch];
				// Bitshift 8 to the left if not on the last iteration
				chunks[i][ui] <<= (ch < 3) ? 8 : 0;
			}
		}
	}

	// De-allocate the character blocks
	for (int i = 0; i < chunk_count; ++i) {
		delete[] chunks_ch[i];
	}
	delete[] chunks_ch;
	chunks_ch = nullptr;

	// Hash each chunk and then add it to the state
	for (int i = 0; i < chunk_count; ++i) {
		loopChunkInto(state, chunks[i]);
	}

	// De-allocate the unsigned long word blocks
	for (int i = 0; i < chunk_count; ++i) {
		delete[] chunks[i];
	}
	delete[] chunks;
	chunks = nullptr;

	// Convert the hash's state variables into hex string
	string hash = "";
	uint32_t currState;
	for (int stateIndex = 0; stateIndex < 5; stateIndex++) {
		currState = state[stateIndex];
		for (int j = 0; j < 8; j++) {
			currState = ROL32(currState, 4);
			short int current = currState & 0xF;
			unsigned char ch = (unsigned char)current;
			hash += toHex(ch);
		}
	}

	return hash;
}