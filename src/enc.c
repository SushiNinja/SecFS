#include "enc.h"

int enc_main(const int argc, const char *argv[]) {
	//fprintf(stderr, "Calling encryption main with args:\n");

	if (argc < 4) {
		fprintf(stderr, "Insufficient arguments.");
		printUsage();
	}

	const char *startup_path = argv[0];
	const char *cipher_name = argv[1];
	const char *digest_name = argv[2];
	const char *rootDir = argv[3];

	int maxKey = 0;

	int i = 0;
	for (i = 0; i < argc; i++) {
		char arg[strlen(argv[i]) + 1];
		strcpy(arg, argv[i]);
		strcat(arg, "\n");
		fprintf(stderr, arg);
	}

	/* cipher_name is used as it's position is the first argument */
	if (strcmp(cipher_name, "-lc") == 0) {
		printAvailableCiphers();
		return 0;
	} else if (strcmp(cipher_name, "-ld") == 0) {
		printAvailableDigests();
		return 0;
	}

	/* Load the human readable error strings for libcrypto */
	ERR_load_crypto_strings();

	/* Load all digest and cipher algorithms */
	OpenSSL_add_all_algorithms();

	/* Load config file, and other important initialisation */
	OPENSSL_config(NULL);

	/*TODO: ... Do some crypto stuff here ... */

	const EVP_CIPHER *cipher = EVP_get_cipherbyname(cipher_name);
	const EVP_MD *dgst = EVP_get_digestbyname(digest_name);
	unsigned char key[EVP_MAX_KEY_LENGTH];
	unsigned char iv[EVP_MAX_IV_LENGTH];
	const char* password = "password";
	const unsigned char *salt = NULL;

	if (!cipher) {
		fprintf(stderr,
				"Error loading %s algorithm, please use a different one.\n"
						"Use -lc to view a list of available ciphers.\n"
						"Example: %s -enc -lc\n", cipher_name, startup_path);
	} else {
		fprintf(stdout, "Successfully loaded %s algorithm.\n", cipher_name);
		maxKey = EVP_CIPHER_key_length(cipher) * 8;
		fprintf(stdout, "Using a %d bit key.\n", maxKey);
	}

	if (!dgst) {
		fprintf(stderr, "Couldn't load digest %s.\n"
				"Use -ld to view a list of available ciphers.\n"
				"Example: %s -enc -ld\n", digest_name, startup_path);
	} else {
		fprintf(stdout, "Successfully loaded %s digest.\n", digest_name);
	}

	if (!EVP_BytesToKey(cipher, dgst, salt, (unsigned char *) password,
			strlen(password), 1, key, iv)) {
		fprintf(stderr, "Key creation failed.\n");
		return 1;
	} else {
		//printf("Key: "); for(i=0; i<cipher->key_len; ++i) { printf("%02x", key[i]); } printf("\n");
		//printf("IV: "); for(i=0; i<cipher->iv_len; ++i) { printf("%02x", iv[i]); } printf("\n");
		fprintf(stdout,"Key succesfully generated\n");
	}

	if(enc_dir_recursive(rootDir)) {

	} else {
		fprintf(stderr,"Encryption failed.\n");
	}

	/* Clean up */

	/* Removes all digests and ciphers */
	EVP_cleanup();

	/* if you omit the next, a small leak may be left when you make use of the BIO (low level API) for e.g. base64 transformations */
	CRYPTO_cleanup_all_ex_data();

	/* Remove error strings */
	ERR_free_strings();

	return 0;
}

int enc_dir_recursive(const char *path){

	struct dirent *pDirent;
	DIR *pDir;

	pDir = opendir(path);
	if(pDir == NULL) {
		fprintf(stderr,"Could not open directory [%s]\n",path);
		return 0;
	}

	while((pDirent=readdir(pDir))!= NULL) {
		if(strcmp(pDirent->d_name,".") == 0 || strcmp(pDirent->d_name,"..") == 0) continue;

		int len = strlen(path) + strlen((unsigned char *)pDirent->d_name) + 1;

		char child[len];

		int i;
		for(i = 0; i < len; i++) child[i] = NULL;

		strcat(child,path);
		strcat(child,"/");
		strcat(child,pDirent->d_name);

		struct stat s;
		if(stat(child,&s) == 0 ){
			if(s.st_mode & S_IFDIR) {
				return enc_dir_recursive(child);
			} else {
				//TODO Load file, and convert to byte array
				/*TODO encrypt byte array here
				EVP_CIPHER_CTX encCtx;
				BYTE *ptr = data;
				int length;

				EVP_CIPHER_CTX_init( &encCtx );
				EVP_EncryptInit( &encCtx, cipher, aesKey, NULL );

				EVP_EncryptUpdate( &encCtx, ptr, &length, data, dataLen );
				ptr += length;
				dataLen = length;

				EVP_EncyptFinal( &encCtx, ptr, &length );
				dataLen += length;
				*/

				//TODO save byte array to the same path as the original file

				//TODO delete original file
			}
		} else {
			return 0;
		}

	}

	closedir(pDir);
	return 1;
}
