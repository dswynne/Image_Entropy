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
#include <sstream>
#include <iostream>
#include <memory>

using std::unique_ptr;
using BN_ptr = std::unique_ptr<BIGNUM, decltype(&::BN_free)>;
using RSA_ptr = std::unique_ptr<RSA, decltype(&::RSA_free)>;
using namespace std;

struct retValsRSA {
    std::string publicKey;
    std::string privateKey;
};

struct retValsAES {
    std::string key;
    std::string iv;

};

retValsRSA convertRSAtoString(RSA* keypair) {

    retValsRSA r;
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

    r.privateKey = pri_key;
    r.publicKey = pub_key;

    return r;

}


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


retValsRSA generateRSAKey(std::string seedString) {


    OpenSSL_add_all_algorithms();
    int rc;
    const int maxSeed = 675000;

    //Only pull last 6 values of string
    std::string subString = seedString.substr(0, 6);
    int seed;

    //Convert string seed to int
    std::istringstream(subString) >> seed;

    //if value is greater than 675000, then only take last 5 values
    if (seed > maxSeed) {
        subString = subString.substr(0, 5);
        std::istringstream(subString) >> seed;
    }
    void* buffer = malloc(sizeof(int));
    RAND_seed(buffer, seed);
  
    RSA_ptr rsa(RSA_new(), ::RSA_free);
    BN_ptr bn(BN_new(), ::BN_free);

    rc = BN_set_word(bn.get(), RSA_F4);
    if (!rc) {
        std::cout << "Error creating BIGNUM\n";
    }

    // Generate RSA key
    rc = RSA_generate_key_ex(rsa.get(), 2048, bn.get(), NULL);
    if (!rc) {
        std::cout << "Error creating RSA Key pair\n";

    }

    print_keypair(rsa.get());

    retValsRSA r = convertRSAtoString(rsa.get());

    return r;
 }


retValsAES generateAESKey(std::string seedString) {

    unsigned char key[16], iv[16];
    retValsAES a;

    //Seed random generation with our own value
    const int maxSeed = 675000;

    //Only pull last 6 values of string
    std::string subString = seedString.substr(0, 6);
    int seed;

    //Convert string seed to int
    std::istringstream(subString) >> seed;

    //if value is greater than 675000, then only take last 5 values
    if (seed > maxSeed) {
        subString = subString.substr(0, 5);
        std::istringstream(subString) >> seed;
    }
    cout << "seed num: " << seed << "\n";
    void* buffer = malloc(sizeof(int));
    RAND_seed(buffer, seed);

    if (!RAND_bytes(key, sizeof key)) {
        /* OpenSSL reports a failure, act accordingly */
    }
    if (!RAND_bytes(iv, sizeof iv)) {
        /* OpenSSL reports a failure, act accordingly */
    }

    //write char keys and iv to string in hex format
    ostringstream keyString;
    ostringstream ivString;
    //cout << "AES Key: ";

    for (int i = 0; i < 16; i++) {
        //cout << hex << (int)key[i] << " ";
        keyString << hex << (int)key[i];

    }

    //cout << "\n";
    //cout << "AES Initialization Vector: ";
    for (int i = 0; i < 16; i++) {
        //cout << hex << (int)iv[i] << " ";
        ivString << hex << (int)iv[i];
    }
    //cout << "\n";

    a.key = keyString.str();
    a.iv = ivString.str();
    return a;
}