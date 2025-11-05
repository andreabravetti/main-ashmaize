#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

uint64_t generate_random_u64() {
    uint64_t limit = 10000000000000000ULL - 1;
    uint64_t r = 0;
    r = ((uint64_t)rand() << 48) | ((uint64_t)rand() << 32) | ((uint64_t)rand() << 16) | ((uint64_t)rand());
    return r % (limit + 1);
}

void convert_to_hex_string(uint64_t num, char* hex_string) {
    snprintf(hex_string, 17, "%016llx", (unsigned long long)num);
}

void result_to_hex_string(const char* result, char* hex_string) {
    int offset = 0;
    for (int i = 0; i < 4; i++) {
        offset += sprintf(hex_string + offset, "%02X", result[i]);
    }
}

unsigned long long convert_hex_to_ull(const char* hex_string) {
    char* endptr = 0;
    return strtoull(hex_string, &endptr, 16);
}

typedef struct Rom Rom;

extern Rom* cinit(const uint8_t* key_ptr, size_t key_len, size_t size);
extern void chash(const uint8_t* salt_ptr, size_t salt_len, const Rom* rom_ptr, uint32_t nb_loops, uint32_t nb_instrs, uint8_t* result);
extern void cfree(Rom* rom);

int main(int argc, char *argv[]) {
    const size_t MB = 1024 * 1024;
    const size_t GB = 1024 * MB;
    char* address = argv[1];
    char* challenge_id = argv[2];
    char* difficulty = argv[3];
    char* no_pre_mine = argv[4];
    char* latest_submission = argv[5];
    char* no_pre_mine_hour = argv[6];
    Rom* rom = cinit(no_pre_mine, strlen(no_pre_mine), 1024*MB);
    int target = (int)strtol(difficulty, NULL, 16);
    time_t start = time(NULL);
    bool found = false;
    uint64_t nonce = 0;
    char nonce_str[17];
    char preimage[257];
    char result[64];
    char hash_hex[9];
    snprintf(result, 7, "result");
    uint64_t hash_int = 0;
    while (time(NULL) - start < 3600) {
        nonce = generate_random_u64();
        convert_to_hex_string(nonce, nonce_str);
        snprintf(
            preimage, 256, "%s%s%s%s%s%s%s",
            nonce_str,
            address,
            challenge_id,
            difficulty,
            no_pre_mine,
            latest_submission,
            no_pre_mine_hour
        );
        chash(preimage, strlen(preimage), rom, 8, 256, result);
        result_to_hex_string(result, hash_hex);
        hash_int = convert_hex_to_ull(hash_hex);
        if ((hash_int | target) == target) {
            found = true;
            break;
        }
    }
    cfree(rom);
    if (found) {
        printf("%s", nonce_str);
        return 0;
    }
    return 1;
}
