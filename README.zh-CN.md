# base
>1. ***本工具完全采用c编写, 在Visual Studio, gun下编译测试通过***
>2. ***建议使用c11标准, 代码段中变量的声明位置不见得兼容c99***
>3. ***不依赖于任何第三方库, 未参考任何项目, 如有雷同纯属巧合***
>4. ***依据base错位编码原理实现, 理论支持任意base编码***

## _功能描述_

### encode

***编码支持的理论上限是128位, 如果要设置更高位数的编码表,<br>
   那么这个表的字符将超越ascii的数量, 那么表本身的编码应该采<br>
   用何种编码规则又是一个考虑问题, 这不在此工具考虑范围之内***

### decode

***解码支持的理论上限同样是128位, 采用散列表方式查找***

## _使用方法_

### encode

1. ***`setTable`方法接受三个参数, 分别是编码表(string)`table`, 编码表长度<br>
   (int)`len`, 填充字符(char)`pad`. 编码表应该优先在进行编码前设置并且<br>
   应该做返回值检验.***
2. ***`encode`方法接受三个参数, 分别是待编码字符串(string)`p_str`, 字符串<br>
   长度(int)`len`, 接收编码结果的buffer(string)`resul`***

### decode

1. ***同上***
2. ***`encode`方法接受三个参数, 分别是待解码字符串(string)`p_str`, 字符串<br>
   长度(int)`len`, 接收解码结果的buffer(string)`resul`***

## _测试例子_

### encode
```
int main(){
	unsigned char bit = 32;
	char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
	setTable(table, bit, '=');
	char* p_str = "https://github.com/";
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
	char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
	unsigned char len = 32;
	char* str = "NB2HI4DTHIXS6Z3JORUHKYROMNXW2LY=";
	setTable(table, len, '=');
	unsigned char* result = (unsigned char*)malloc(44 * sizeof(char));
	decode(str, 56, result);
	printf("%s", result);
	return 0;
}
```
> https://github.com/

## _注意事项_

1. ***`len`的长度务必准确, 否则可能造成结果的错误***
2. ***你可能会看到编码的结果与其它工具不一致的情况, 一般出现在宽字符编码上, <br>
   这并不是代码的错误, 这是字符串本身编码的问题, 在windows机器上, 普遍采用的<br>
   是GBK编码, 这导致字符串先以gbk的二进制编码形式存储, 再被该代码处理, 要解决<br>
   这个问题, 应该事先同一编码, 一般是utf-8***
3. ***代码做了一些边界判断, 但仍不排除可能存在的内存泄露, 应该注意`len`, `result`<br>
   的空间问题, 以及输入字符串的意外字符***