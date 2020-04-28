#pragma once
/*-----------
Contains functions for RSA key generation and AES key generation
-------------*/


#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/rand.h>
#include <string>
#include <iostream>
#include <memory>

using std::unique_ptr;
using BN_ptr = std::unique_ptr<BIGNUM, decltype(&::BN_free)>;
using RSA_ptr = std::unique_ptr<RSA, decltype(&::RSA_free)>;



void print_keypair(RSA* keypair) {
    // To get the C-string PEM form:
    BIO* pri = BIO_new(BIO_s_mem());
    BIO* pub = BIO_new(BIO_s_mem());

    PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);
    PEM_write_bio_RSAPublicKey(pub, keypair);

    size_t pri_len = BIO_pending(pri);
    size_t pub_len = BIO_pending(pub);

    char* pri_key, * pub_key;
    pri_key = (char*)malloc(pri_len + 1);
    pub_key = (char*)malloc(pub_len + 1);

    BIO_read(pri, pri_key, pri_len);
    BIO_read(pub, pub_key, pub_len);

    pri_key[pri_len] = '\0';
    pub_key[pub_len] = '\0';

    printf("\n%s\n\n%s\n", pri_key, pub_key);

    BIO_free_all(pub);
    BIO_free_all(pri);
    free(pri_key);
    free(pub_key);
}


void generateRSAKey(std::string seed) {

    OpenSSL_add_all_algorithms();

    int rc;

    const void* buffer;
    //buffer = seed.length * malloc(sizeof(char));

    //convert seed string to num
    //std::string::size_type sz;   // alias of size_t
    //int numSeed = std::stoi(seed, &sz);

    //Seed key pair generation with our seed
    //RAND_seed(buffer, numSeed);

    RSA_ptr rsa(RSA_new(), ::RSA_free);
    BN_ptr bn(BN_new(), ::BN_free);

    rc = BN_set_word(bn.get(), RSA_F4);
    if (!rc) {
        std::cout << "Error creating BIGNUM\n";
    }

    //bn.get() is the seed and should be replaced with our number that we want to use to seed the RSA key

    // Generate RSA key
    rc = RSA_generate_key_ex(rsa.get(), 2048, bn.get(), NULL);
    if (!rc) {
        std::cout << "Error creating RSA Key pair\n";

    }

    print_keypair(rsa.get());

  
    return;
}


void generateAESKey() {

    unsigned char key[16], iv[16];

    //Seed random generation with our own value
    //Could use a 16 or 32 bits from our random number to be used here
    unsigned int num;
    //RAND_seed(const void *buf, int num)

    if (!RAND_bytes(key, sizeof key)) {
        /* OpenSSL reports a failure, act accordingly */
    }
    if (!RAND_bytes(iv, sizeof iv)) {
        /* OpenSSL reports a failure, act accordingly */
    }

    //Display char key in hex
    std::cout << "AES Key: ";

    for (int i = 0; i < 16; i++) {
        std::cout << std::hex << (int)key[i] << " ";
    }
    std::cout << "\n";
    std::cout << "AES Initialization Vector: ";
    for (int i = 0; i < 16; i++) {
        std::cout << std::hex << (int)iv[i] << " ";
    }
    std::cout << "\n";

}