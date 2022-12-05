#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include "crypt.h"
#include "util.h"

char *md5sum(unsigned char *str){
        unsigned char md5digest[MD5_DIGEST_LENGTH];
        unsigned int s_len = (unsigned int)strlen((const char*)str);
        //MD5_CTX md5handler;
        char *output = NULL;
        size_t output_len = 32 + ADDON_ASMEM;

        MD5(str, s_len, md5digest);
        output = (char *)malloc(output_len);
        memset(output, '\0', output_len);

        int j = 0;
        for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
                sprintf((char *)(output + j),"%02x", md5digest[i]);
                j += 2;
        };

        return output;
}
