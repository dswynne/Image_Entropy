#include <memory>
using std::unique_ptr;

#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/rand.h>
#include <string>

#include <cassert>
#define ASSERT assert

using BN_ptr = std::unique_ptr<BIGNUM, decltype(&::BN_free)>;
using RSA_ptr = std::unique_ptr<RSA, decltype(&::RSA_free)>;
using EVP_KEY_ptr = std::unique_ptr<EVP_PKEY, decltype(&::EVP_PKEY_free)>;
using BIO_FILE_ptr = std::unique_ptr<BIO, decltype(&::BIO_free)>;

/*
-----------------------------------------------------------------------------------------------------------------------------
Test code from:
https://stackoverflow.com/questions/5927164/how-to-generate-rsa-private-key-using-openssl

Produces an RSA key and then converts the public and private keys into different formats for display

Further relevant information:
https://stackoverflow.com/questions/20065304/differences-between-begin-rsa-private-key-and-begin-private-key
-----------------------------------------------------------------------------------------------------------------------------
*/

//void generateRSAKey(std::string seed){
//    int rc;
// 
//    const void* buffer;
//    //buffer = seed.length * malloc(sizeof(char));
//
//    //convert seed string to num
//    std::string::size_type sz;   // alias of size_t
//    int numSeed = std::stoi(seed, &sz);
//
//    //Seed key pair generation with our seed
//    RAND_seed(buffer, numSeed);
//
//    RSA_ptr rsa(RSA_new(), ::RSA_free);
//    BN_ptr bn(BN_new(), ::BN_free);
//
//    BIO_FILE_ptr pem1(BIO_new_file("rsa-public-1.pem", "w"), ::BIO_free);
//    BIO_FILE_ptr pem2(BIO_new_file("rsa-public-2.pem", "w"), ::BIO_free);
//    BIO_FILE_ptr pem3(BIO_new_file("rsa-private-1.pem", "w"), ::BIO_free);
//    BIO_FILE_ptr pem4(BIO_new_file("rsa-private-2.pem", "w"), ::BIO_free);
//    BIO_FILE_ptr pem5(BIO_new_file("rsa-private-3.pem", "w"), ::BIO_free);
//    BIO_FILE_ptr der1(BIO_new_file("rsa-public.der", "w"), ::BIO_free);
//    BIO_FILE_ptr der2(BIO_new_file("rsa-private.der", "w"), ::BIO_free);
//
//    rc = BN_set_word(bn.get(), RSA_F4);
//    ASSERT(rc == 1);
//
//    //bn.get() is the seed and should be replaced with our number that we want to use to seed the RSA key
//
//    // Generate RSA key
//    rc = RSA_generate_key_ex(rsa.get(), 2048, bn.get(), NULL);
//    ASSERT(rc == 1);
//
//    // Convert RSA to PKEY
//    EVP_KEY_ptr pkey(EVP_PKEY_new(), ::EVP_PKEY_free);
//    rc = EVP_PKEY_set1_RSA(pkey.get(), rsa.get());
//    ASSERT(rc == 1);
//
//    //////////
//
//    // Write public key in ASN.1/DER
//    rc = i2d_RSAPublicKey_bio(der1.get(), rsa.get());
//    ASSERT(rc == 1);
//
//    // Write public key in PKCS PEM
//    rc = PEM_write_bio_RSAPublicKey(pem1.get(), rsa.get());
//    ASSERT(rc == 1);
//
//    // Write public key in Traditional PEM
//    rc = PEM_write_bio_PUBKEY(pem2.get(), pkey.get());
//    ASSERT(rc == 1);
//
//    //////////
//
//    // Write private key in ASN.1/DER
//    rc = i2d_RSAPrivateKey_bio(der2.get(), rsa.get());
//    ASSERT(rc == 1);
//
//    // Write private key in PKCS PEM.
//    rc = PEM_write_bio_PrivateKey(pem3.get(), pkey.get(), NULL, NULL, 0, NULL, NULL);
//    ASSERT(rc == 1);
//
//    // Write private key in PKCS PEM
//    rc = PEM_write_bio_PKCS8PrivateKey(pem4.get(), pkey.get(), NULL, NULL, 0, NULL, NULL);
//    ASSERT(rc == 1);
//
//    // Write private key in Traditional PEM
//    rc = PEM_write_bio_RSAPrivateKey(pem5.get(), rsa.get(), NULL, NULL, 0, NULL, NULL);
//    ASSERT(rc == 1);
//
//    return;
//}
//
//void generateAESKey() {
//
//    unsigned char key[16], iv[16];
//
//    //Seed random generation with our own value
//    //Could use a 16 or 32 bits from our random number to be used here
//    unsigned int num;
//    //RAND_seed(const void *buf, int num)
//
//    if (!RAND_bytes(key, sizeof key)) {
//        /* OpenSSL reports a failure, act accordingly */
//    }
//    if (!RAND_bytes(iv, sizeof iv)) {
//        /* OpenSSL reports a failure, act accordingly */
//    }
//
//
//
//}