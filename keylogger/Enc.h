#ifndef ENC_H
#define ENC_H

#include <string>
#include <vector>
#include <cstdlib>

namespace Enc
{
 std::string enc_encode(const std::string &);

 const std::string &SALT1 = "this_is_salt_1";
 const std::string &SALT2 = "this_is_salt_2";
 const std::string &SALT3 = "this_is_salt_3";
 int n = 7;  //(rand()%14);
 int r = 6;  //rand()%13);
 int t = 5;  //(rand()%12);

 std::string EncryptB64(std::string s)  //psuedo encryption - need to use base64 so no outside libraries used
 {
     s = SALT1 + s + SALT2 + SALT3;
     s = enc_encode(s);
     s.insert(n, SALT3);
     s += SALT2;
     s = enc_encode(s);
     s = SALT1 + SALT2 + SALT3;
     s = enc_encode(s);
     s.insert(r, "4");
     s.insert(t, "5");
     return s;
 }

 const std::string &ENC_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

 std::string enc_encode(const std::string &s)
 {
     std::string ret;
     int val = 0;
     int bits = -6;
     const unsigned int b63 = 0x3F;

     for(const auto &c : s)
     {
         val = (val << 8) + c;
         bits += 8;
         while(bits >=0)
         {
             ret.push_back(ENC_CODES[(val>>bits) & b63]);
             bits -=6;
         }
     }
     if(bits> -6)
        ret.push_back(ENC_CODES[((val << 8) >> (bits +8)) & b63]);

     while (ret.size() %4)
        ret.push_back('=');

     return ret;
 }
}



#endif // ENC_H
