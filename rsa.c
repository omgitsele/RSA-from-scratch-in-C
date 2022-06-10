#include "rsa.h"
#include "utils.h"
#include "stdbool.h"


/*
 * Sieve of Eratosthenes Algorithm
 * https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 *
 * arg0: A limit
 * arg1: The size of the generated primes list. Empty argument used as ret val
 *
 * ret:  The prime numbers that are less or equal to the limit
 */
size_t *
sieve_of_eratosthenes(int limit, int *primes_sz)
{
	size_t *primes;
	bool prime_no[limit+1];
	
	for (size_t i = 0; i < limit; i++)
	{
		prime_no[i] = true;
	}
	size_t total_primes = 0;
	for (size_t p = 2; p <= limit; p++)
	{
		if (prime_no[p])
		{
			total_primes++;
			// Update all multiples of p
			for (int i = p * p; i <= limit; i += p)
				prime_no[i] = false;
		}
	}

	printf("Total primes: %ld\n", total_primes);
	*primes_sz = total_primes;
	primes = (size_t*)malloc( sizeof(size_t)*total_primes );
	size_t c = 0;
	for (size_t i = 2; i < limit+1; i++)
	{
		if (prime_no[i])
		{
			primes[c] = i;
			c++;
		}
		
	}

	return primes;
}


/*
 * Greatest Common Denominator
 *
 * arg0: first number
 * arg1: second number
 *
 * ret: the GCD
 */
int
gcd(int a, int b)
{

	int gcd;
  	for(int i=1; i <= a && i <= b; ++i)
	{
		if(a%i==0 && b%i==0)
			gcd = i;
  	}
	return gcd;

}


/*
 * Chooses 'e' where 
 *     1 < e < fi(n) AND gcd(e, fi(n)) == 1
 *
 * arg0: fi(n)
 *
 * ret: 'e'
 */
size_t
choose_e(size_t fi_n)
{
	size_t e;

	/* TODO */

	return e;
}


/*
 * Calculates the modular inverse
 *
 * arg0: first number
 * arg1: second number
 *
 * ret: modular inverse
 */
size_t
mod_inverse(size_t a, size_t b)
{

	for (int x = 1; x < b; x++)
		if ((((a%b) * (x%b)) % b) == 1)
			return x;
	return 1;

}


/*
 * Generates an RSA key pair and saves
 * each key in a different file
 */
void
rsa_keygen(void)
{
	size_t p;
	size_t q;
	size_t n;
	size_t fi_n;
	size_t e;
	size_t d;
	size_t *primes;
	int *primes_sz = (int*)malloc(sizeof(int*));

	//Generate a pool of primes using the Sieve Of Eratosthenes
	primes = sieve_of_eratosthenes(RSA_SIEVE_LIMIT, primes_sz);
	printf("Number of primes: %d\n", *primes_sz);

	
	//Initialize the random number generator with a changing source (the time function)
	srand ( time(NULL) );

	//Pick two random primes from the pool. Lets name them p and q.
	p = primes[rand()%*primes_sz];
	q = primes[rand()%*primes_sz];

	//Compute n where n = p * q.
	n = p * q;

	//Calculate fi(n) where fi(n) = (p - 1) * (q - 1). his is Euler’s totient function, as described
	//in the original RSA paper "A Method for Obtaining Digital Signatures and Public-Key Cryptosystems”.
	fi_n = (p-1) * (q - 1);

	//Choose a prime number e where (e % fi(n) != 0) AND (gcd(e, fi(n)) == 1) where gcd() is
	//the Greatest Common Denominator.
	while (true)
	{
		e = primes[rand()%*primes_sz];

		if (e % fi_n != 0 && gcd(e, fi_n) == 1)
		{
			break;
		}
				
	}

	//Choose d where d is the modular inverse of (e,fi(n))
	d = mod_inverse(e, fi_n);

	//store the public and private keys in the files public.key and
	//private.key respectively.

	//Public key file
	FILE *public = fopen("public.key","w");
	fwrite(&n, sizeof(size_t), 1, public);
	fwrite(&d, sizeof(size_t), 1, public);
	fclose(public);
	printf("Public key is: n: %ld d: %ld\n",n,d);

	//Private key file
	FILE *private = fopen("private.key","w");
	fwrite(&n, sizeof(size_t), 1, private);
	fwrite(&e, sizeof(size_t), 1, private);
	fclose(private);
	printf("Private key is: n: %ld e: %ld",n,e);

	free(primes);
	free(primes_sz);

}


/*
 * Encrypts an input file and dumps the ciphertext into an output file
 *
 * arg0: path to input file
 * arg1: path to output file
 * arg2: path to key file
 */
void
rsa_encrypt(char *input_file, char *output_file, char *key_file)
{

	FILE *in_file = fopen(input_file, "r");
	FILE *out_file = fopen(output_file, "w");
	FILE *keyFile = fopen(key_file, "r");


	size_t *key;
	key = (size_t*)malloc(sizeof(size_t)*2); // we have two keys of type size_t 

   	/* Read the key (public or private) */
	if (!fread(key, sizeof(size_t), 2, keyFile))
	{
		printf("Error reading the key\n");
	}
	
   	
	//Display the key
	//printf("Key: n: %ld d:%ld",key[0], key[1]);
	fseek(in_file, 0, SEEK_END);
	int size = ftell(in_file);
	fseek(in_file, 0, SEEK_SET);
	char *inputFileMemory = (char*)malloc(sizeof(char*)*size);
	// Read the content of the file
	if (!fread(inputFileMemory,1,size,in_file)) 
	{
    	printf("Error reading the file\n");
  	}
	// Allocate memory for the ciphertext
	size_t *cipherText = (size_t*)malloc(sizeof(size_t*)*size);
	// Print the original content as number
	printf("OG is: ");
	for (size_t i = 0; i < size; i++)
	{
		printf("%ld",(size_t)inputFileMemory[i]);
	}
	printf("\n");
	// Encrypt the content using modular exponentiation
	for (size_t i = 0; i < size; i++)
	{
		cipherText[i] = (size_t) myexpomod((size_t)inputFileMemory[i],key[1], key[0]);
	}
	printf("Cipher text is: %ld\n", *cipherText);
	
	// Print the ciphertext
	for (size_t i = 0; i < size; i++)
	{
		printf("%ld",cipherText[i]);
	}

	// Write the ciphertext to the output file
	fwrite(cipherText, sizeof(size_t), size, out_file);

	// Clean up
	fclose(in_file);
	fclose(out_file);
	fclose(keyFile);
	free(inputFileMemory);
	free(cipherText);
	return;
		
		

}


/*
 * Decrypts an input file and dumps the plaintext into an output file
 *
 * arg0: path to input file
 * arg1: path to output file
 * arg2: path to key file
 */
void
rsa_decrypt(char *input_file, char *output_file, char *key_file)
{
	FILE *in_file = fopen(input_file, "r");
	FILE *out_file = fopen(output_file, "w");
	FILE *keyFile = fopen(key_file, "r");

	size_t *key = (size_t*)malloc(sizeof(size_t)*2);
	// Read the key (public or private depending on the input file)
	if (!fread(key,sizeof(size_t),2,keyFile)) {
    	printf("Error reading file\n");
  	}

	fseek(in_file, 0, SEEK_END);
  	size_t size = ftell(in_file);
  	fseek(in_file, 0, SEEK_SET);
	// Allocate memory for the ciphertext
	size_t *encrypted = (size_t*)malloc(sizeof(size_t*)*size/8);
	if (!fread(encrypted,sizeof(size_t),size/8,in_file)) {
    	printf("Error reading file\n");
  	}
	// Allocate memory for the plaintext both as characters and as size_t
	char *plaintext = (char*)malloc(sizeof(char*)*size/8);
	size_t *message = (size_t*)malloc(sizeof(size_t*)*size/8);
	// Print the plaintext as number
	printf("\nOG as number is: \n");
	for (int i = 0; i < size/8; i++) {
		message[i] = myexpomod(encrypted[i], key[1], key[0]);
		printf("%ld",message[i]);
	}
	// Print the plaintext as a string
	printf("\nOG as string is: \n");
	for (int i = 0; i < size/8; i++) {
		printf("%c",(char)message[i]);
		plaintext[i] = (char)message[i];
	}

	printf("\nFile %s has been decrypted and stored in: %s\n", input_file, output_file);
	fwrite(plaintext, sizeof(char), size/8, out_file);

	fclose(in_file);
	fclose(out_file);
	fclose(keyFile);
	free(message);
	free(encrypted);
	free(plaintext);
	return;
	

}
/*
 * https://simple.wikipedia.org/wiki/Modular_exponentiation
*/
int 
myexpomod(size_t m, size_t e, size_t n)
{
	int r = 1;
	m = m%n;
	while(e>0)
	{
		if (e%2 != 0)
		{
			r = (r*m)%n;
		}
		e = e/2;
		m = (m*m)%n;
	}
	return r;
}