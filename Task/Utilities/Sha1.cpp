// Sha1.cpp
// Task
// CIS 22C F2016: Matthew Tso
//
//  Following: http://www.metamorphosite.com/one-way-hash-encryption-sha1-data-software
//  Warning! Only works with up to 55-length strings
//  because only a single chunk is hashed.

#include "Sha1.h"

using namespace std;

// Bit rotation macros
#define ROL8(num, shift)   ( (num << shift) | (num >> ( 8 - shift)) )
#define ROL64(num, shift)  ( (num << shift) | (num >> (64 - shift)) )
#define ROL32(num, shift)  ( (num << shift) | (num >> (32 - shift)) )
#define ROR32(num, shift)  ( (num >> shift) | (num << (32 - shift)) )

const int CHUNKCH_SIZE = 64; // 64 unsigned char in one 512 bit chunk
const int CHUNKUL_SIZE = 16; // 16 uint32 in one 512 bit chunk
const int CHUNKXT_SIZE = 80; // 80 uint32 'words' in the main loop
const uint32_t STATE_INIT[5] = {  // initial 5 word constants
    0x67452301,
    0xEFCDAB89,
    0x98BADCFE,
    0x10325476,
    0xC3D2E1F0
};

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

void hashLoop(uint32_t* state, uint32_t* chunk_in)
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

	// MARK: 10: Initialize variables with state constants
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

string task::sha_1(const string& input) 
{
    if (input.length() > 55) { return "Hashing 55+ char input has not been implemented yet."; }
        
    unsigned char chunk_ch[CHUNKCH_SIZE] = { 0 };
    uint32_t chunk_l[CHUNKUL_SIZE] = { 0 };
    uint32_t state[5];

	int length = (int)input.length();

	// Initialize state with constants
    for (int i = 0; i < 5; i++) {
		state[i] = STATE_INIT[i];
    }
    
	// TODO: Create more than one chunk for long inputs.
    // MARK: Step 4 & 5: Append input characters into chunk
    for (int i = 0; i < input.length(); ++i) {
        chunk_ch[i] = input[i];
    }
    chunk_ch[input.length()] = 1 << 7; // append 1 to end
    
    // MARK: 6.1: Append original message length
    // Multiply string length by character bit size
    uint64_t length_64 = (input.length() * 8);
    // Mask off by character and shift bits left by 8
    for (int i = 1; i <= 8; i++) {
        chunk_ch[CHUNKCH_SIZE - i] = (length_64) & 0xFF;
        length_64 >>= 8;
    }
    
    // MARK: 8: Convert chunk of 64 char into 16 uint32 'words'
    for (int i = 0; i < CHUNKUL_SIZE; i++) {
        // Add chunk
        for (int chi = 0; chi < 4; chi++) {
            chunk_l[i] = chunk_l[i] | chunk_ch[i * 4 + chi];
            chunk_l[i] <<= (chi < 3) ? 8 : 0;
        }
    }

	hashLoop(state, chunk_l);
    
    // Convert hash variables into hex string
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
