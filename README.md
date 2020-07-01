# fcypt
> Quick file encryption/decryption via AES(ECB) 


## filename extension:

* __.key:__ 128-bits key,which should be kept separately from your encrypted file
* __.en:__ encrypted file
* __.de:__ decrypted file that is the same as your original file after the extension being stripped

## Build
git clone https://github.com/nichtsen/fcrypt.git
cd fcrypt
make 

## Usage
ecb -en \<your file waits to be encrypted\>

ecb -de \<your file has been encrypted and waits to be decrypted\>

## Language
[python implementation](https://github.com/nichtsen/symk-fcrypto)
[golang implementation](https://github.com/nichtsen/fcypt)
