def decrypt_flag(enc_flag):
    key = 'qwertyuioplkjhgfdsazlfmhkb'
    x = list(enc_flag)
    n = len(x)
    
    # Work backwards from the last recursive step (n-1) down to 0
    for current_n in range(n - 1, -1, -1):
        for i in range(current_n, len(x)):
            x[i] = chr(ord(x[i]) ^ ord(key[i - current_n]))
            
    return ''.join(x)

ciphertext = "\"4Rj\x12(\\_^(,{\x00c\r,OS]e$j\x18,Dl"
print(decrypt_flag(ciphertext))

