# base

[![CN](https://img.shields.io/badge/Language-Chinese-red)](https://github.com/bitjerry/base/blob/main/README.zh-CN.md)
[![APM](https://img.shields.io/badge/license-MIT-2345.svg)](https://github.com/bitjerry/base)

>1. ***this tool is completely written in C, compiled and tested under visual studio and gun***
>2. ***C11 standard is recommended, and the declaration position of variables in the code segment       is not necessarily compatible with C99***
>3. ***does not rely on any third-party library and does not refer to any project. If there is any      similarity, it is pure coincidence***
>4. ***it is implemented according to the principle of base dislocation coding, and theoretically       supports arbitrary base coding***

## _Function description_
### encode
***The theoretical upper limit of coding support is 128 bits. If you want to<br>
   set a coding table with higher bits, then the number of characters in <br>
   this table will exceed the number of ASCII, and the encoding of the table<br>
   itself should be what coding rules to use is another consideration,which<br>
   is beyond the scope of this tool.***
### decode
***The theoretical upper limit supported by decoding is also 128 bits, which <br>
   is searched by hash table.***

## _Method of use_
### encode
1. ***`setTable`funtion accepts three parameters: code table (string)`table`, <br>
   and the length of code table (int)`len`, padding character (char)`pad`. <br>
   The encoding table should be set prior to encoding and return value <br>
   verification
   should be done.***
2. ***`encode`funtion accepts three parameters, namely, the string to be <br>
   encoded. (string)`p_str` the length of string (int)`len`, and buffer <br>
   (string)`result` for receiving encoding results***
### decode
1. ***ditto***
2. ***`encode`funtion accepts three parameters, namely, the string to be <br>
   decoded (string)`str` the length of string (int)`len`, and (string)`result`***

## _Test example_
### encode
```
int main(){
	unsigned char bit = 32;
	char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
	setTable(table, bit, '=');
	char* p_str = " https://github.com/ ";
	char* result = (char*)malloc(100 * sizeof(char));
	encode(p_str, strlen(p_str), result);
	printf("%s\n", result);
	return 0;
}
```
> NB2HI4DTHIXS6Z3JORUHKYROMNXW2LY=
### decode
```
int main() {
	unsigned char bit = 32;
	char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
	setTable(table, bit, '=');
	char* str = "NB2HI4DTHIXS6Z3JORUHKYROMNXW2LY=";
	unsigned char* result = (unsigned char*)malloc(44 * sizeof(char));
	decode(str, strlen(str), result);
	printf("%s", result);
	return 0;
}
```
> https://github.com/

## _Precautions_
1. ***The length of `str` must be accurate, otherwise the result may be wrong***
2. ***you may see that the encoding result is inconsistent with that of other<br>
   tools, usually in wide character encoding. This is not a code error. It is a<br>
   problem with the encoding of the string itself. It is commonly used on <br>
   Windows machines. Usually using UTF-8 code to solve the problem***
3. ***code has made some boundary judgments, but it still does not rule out <br>
   possible memory leakage. It should be noted that`len`,`result` unexpected <br>
   characters in the input string***

## License
MIT © [bitjerry](https://github.com/bitjerry/base/blob/main/LICENSE)
----------
*2021/11/22
*Mr.lin*