// AlgoCollectionMain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



/// <summary>
/// Reverts the string.
/// </summary>
/// <param name="str">The string.</param>
/// <param name="from">From index</param>
/// <param name="to">To index</param>
void revertString(char* str, int from, int to){
	while(from < to){
		char tmp = str[from];
		str[from++] = str[to];
		str[to--] = tmp;
	}

}

/// <summary>
///旋转字符串
///将一个字符串分成X和Y两个部分，在每部分字符串上定义反转操作，如X^T，
///即把X的所有字符反转（如，X=“abc”，那么X^T=“cba”），那么就得到下面的结论：(X^TY^T)^T=YX，显然就解决了字符串的反转问题。
/// </summary>
/// <param name="str">The string.</param>
/// <param name="n">The string length.</param>
/// <param name="m">The rotate index.</param>
void leftRotateString(char* str, int n, int m){
	revertString(str, 0, m-1);
	revertString(str, m, n-1);
	revertString(str, 0, n-1);
}



/// <summary>
/// 单词翻转
/// 输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变，句子中单词以空格符隔开。
/// 为简单起见，标点符号和普通字母一样处理。例如，输入“I am a student.”，则输出“student. a am I”。
/// Reverse the whole string, then reverse each word
/// </summary>
/// <param name="str">The string.</param>
/// <param name="n">The n.</param>
void revertWordInString(char* str, int n){
	//first revert the whole string
	revertString(str, 0, n - 1);
	//then revert each word
	int from = 0;
	int to = 1;
	while (from < n){
		while(from < n && str[from] == ' ') from++;
		to = from + 1;
		while(to < n && str[to] != ' ') to++;
		revertString(str, from, to - 1);
		from = to + 1;
	
	}
}


/// <summary>
///字符串转整数
/// need to consider below situations:
///空指针输入：输入的是指针，在访问空指针时程序会崩溃，因此在使用指针之前需要先判断指针是否为空。
///正负符号：整数不仅包含数字，还有可能是以’+‘或’-‘开头表示正负整数，因此如果第一个字符是’-'号，则要把得到的整数转换成负整数。
///非法字符：输入的字符串中可能含有不是数字的字符。因此，每当碰到这些非法的字符，程序应停止转换。
///整型溢出：输入的数字是以字符串的形式输入，因此输入一个很长的字符串将可能导致溢出。
/// </summary>
/// <param name="str">The string.</param>
/// <returns></returns>
int strToInt(const char* str){
	static const int MAX_INT = (int)((unsigned)~0 >>1);
	static const int MIN_INT = -(int)((unsigned)~0 >> 1) - 1; //TODO: why this is min_int
	if (str == NULL){
		return 0;
	}
    unsigned int n = 0;

	//handle space
	while(_istspace(*str))
		++str;

	//handle sign
	int sign = 1;
	if (*str == '+' || *str == '-')
	{
		if(*str == '-')
			sign = -1;
		++str;
	}

	while(_istdigit(*str))
	{
		int c = *str - '0';
		
		//handle overflow
		if (sign > 0 && (n > MAX_INT / 10 || (n == MAX_INT / 10 && c > MAX_INT % 10))){
			n =  MAX_INT;
			break;
		}
		else if (sign < 0 && (n > (unsigned)MIN_INT / 10 ||(n == (unsigned)MIN_INT / 10 &&  c> (unsigned)MIN_INT % 10)))
		{
			n = MIN_INT;
			break;
		}
		n =  n  * 10  + c;
		++str;
	}

	return sign > 0?n:-(int)n;

}


/// <summary>
/// 判断一个字串是否是回文
/// 同时从字符串头尾开始向中间扫描字串，如果所有字符都一样，那么这个字串就是一个回文。采用这种方法的话，我们只需要维护头部和尾部两个扫描指针即可。
/// 对于栈的话，只需要将字符串全部压入栈，然后依次将各字符出栈，这样得到的就是原字符串的逆置串，分别和原字符串各个字符比较，就可以判断了
/// </summary>
/// <param name="s">The s.</param>
/// <param name="n">The length.</param>
/// <returns></returns>
bool isPalindrome(const char* s, int n){
	if (s == NULL || n < 1)   {
		return false;
	}

	const char* front, *back;
	front = s;
	back = s + n - 1;

	while(front < back){
		if (*(front++) != *(back--)){
			return false;
		}
	}

	return true;

}


/// <summary>
/// 判断字符包含
/// 给定两个分别由字母组成的字符串A和字符串B，字符串B的长度比字符串A短。请问，如何最快地判断字符串B中所有字母是否都在字符串A里？
/// 对字符串A，用位运算（26bit整数表示)计算出一个“签名”，再用B中的字符到A里面进行查找。
/// “最好的方法”，时间复杂度O(n + m)，空间复杂度O(1)
/// </summary>
/// <param name="source">The source.</param>
/// <param name="sourceLen">Length of the source.</param>
/// <param name="pattern">The pattern.</param>
/// <param name="patternLen">Length of the pattern.</param>
/// <returns></returns>
bool stringContains(const char* source, int sourceLen, const char* pattern, int patternLen) {
	int hash = 0;
	for (int i = 0; i< sourceLen; i++) {
		hash |= (1 << (source[i] - 'A'));
	}
	for (int i = 0; i < patternLen; i++) {
		if ((hash & (1 << (pattern[i] - 'A'))) == 0) {
			return false;
		}
	}
	return true;

}

int _tmain(int argc, _TCHAR* argv[])
{
	char testString[] = "teststring";
	leftRotateString(testString, strlen(testString), 4);

	char testSentence[] = "I'm still     working here";
	revertWordInString(testSentence, strlen(testSentence));

	int value = strToInt("  -12345");

	bool ispalin = isPalindrome("madam", strlen("mada1m"));

	char source[] = "ABCDE";
	char pattern[] = "CDE";
	bool contains = stringContains(source, strlen(source), pattern, strlen(pattern));

	return 0;
}
