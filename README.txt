Dimitrios Eleftheriadis 2015030067

"Assignement 4.pdf" has all the necessary information about this project. 

gcc --version: gcc (Ubuntu 9.3.0-17ubuntu1~20.04)

Run "make clean" and then "make all" to build the code

The folder contains:
    -rsa.c: 
        This C file contains the code used for encryption and decryption of given files using generated
        keys. More specifically it uses the Sieve of Eratosthenis to create a public and a private key 
        and stores them to two different files (one called public.key and the other private.key). Depending
        on the input arguments it will either encrypt a given plaintext from the input file or decrpyt a ciphertext
        from the input file and store the result to a new file.

        E.g. Task D
        
        ./assign_3 -g
        
            - The tool will generate a public and a private key and store them in the files public.key and
            private.key respectively.

        ./assign_3 -i hpy414_encryptme_pub.txt -o TUC2015030067_encrypted_pub.txt -k hpy414_public.key -e
        
            - The tool takes as inputs the files "hpy414_encryptme_pub.txt" which contains the plaintext and 
            "hpy414_public.key" which contains the public key. It will then encrypt the plaintext and store the result
            into "TUC2015030067_encrypted_pub.txt".

        ./assign_3 -i hpy414_decryptme_pub.txt -o TUC2015030067_decrypted_pub.txt -k hpy414_public.key -d
            
            - The tool takes as inputs the files "hpy414_decryptme_pub.txt" which contains the ciphertext and 
            "hpy414_public.key" which contains the public key. It will then decrypt the ciphertext and store the result
            into "TUC2015030067_decrypted_pub.txt".
            The result was: "This file was successfully decrypted with the public key."

        ./assign_3 -i hpy414_encryptme_priv.txt -o TUC2015030067_encrypted_priv.txt -k hpy414_private.key -e
        
            - The tool takes as inputs the files "hpy414_encryptme_priv.txt" which contains the plaintext and 
            "hpy414_private.key" which contains the private key. It will then encrypt the plaintext and store the result
            into "TUC2015030067_encrypted_priv.txt".
        
        ./assign_3 -i hpy414_decryptme_priv.txt -o TUC2015030067_decrypted_priv.txt -k hpy414_private.key -d

            - The tool takes as inputs the files "hpy414_decryptme_priv.txt" which contains the ciphertext and 
            "hpy414_private.key" which contains the private key. It will then decrypt the ciphertext and store the result
            into "TUC2015030067_decrypted_priv.txt".
            The result was: "This file was successfully decrypted with the private key."

    -rsa.h:
        The header file of rsa.c
    
    - main.c:
        This C file contains the main() function which reads the input arguments and calls the respective method from rsa.c

    -main.h: 
        The header file of main.c

    - utils.c
        This C file was given which contains some pre-written helper functions.

    -utils.h
        The header file of utlis.c

    - Encrypted files:
        "hpy414_encryptme_pub.txt"
        "hpy414_encryptme_priv.txt"
        "TUC2015030067_encrypted_priv.txt"
        "TUC2015030067_encrypted_pub.txt"
    
    - Decrypted files:
        "hpy414_decryptme_pub.txt"
        "hpy414_decryptme_priv.txt"
        "TUC2015030067_decrypted_pub.txt"
        "TUC2015030067_decrypted_priv.txt"
    
    - Makefile
        This is the file that contains the commands used to build the project.
    
    - assign_3
        The executable file.
