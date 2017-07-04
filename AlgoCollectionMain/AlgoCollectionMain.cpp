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
///��ת�ַ���
///��һ���ַ����ֳ�X��Y�������֣���ÿ�����ַ����϶��巴ת��������X^T��
///����X�������ַ���ת���磬X=��abc������ôX^T=��cba��������ô�͵õ�����Ľ��ۣ�(X^TY^T)^T=YX����Ȼ�ͽ�����ַ����ķ�ת���⡣
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
/// ���ʷ�ת
/// ����һ��Ӣ�ľ��ӣ���ת�����е��ʵ�˳�򣬵��������ַ���˳�򲻱䣬�����е����Կո��������
/// Ϊ������������ź���ͨ��ĸһ���������磬���롰I am a student.�����������student. a am I����
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
///�ַ���ת����
/// need to consider below situations:
///��ָ�����룺�������ָ�룬�ڷ��ʿ�ָ��ʱ���������������ʹ��ָ��֮ǰ��Ҫ���ж�ָ���Ƿ�Ϊ�ա�
///�������ţ����������������֣����п������ԡ�+����-����ͷ��ʾ������������������һ���ַ��ǡ�-'�ţ���Ҫ�ѵõ�������ת���ɸ�������
///�Ƿ��ַ���������ַ����п��ܺ��в������ֵ��ַ�����ˣ�ÿ��������Щ�Ƿ����ַ�������Ӧֹͣת����
///�����������������������ַ�������ʽ���룬�������һ���ܳ����ַ��������ܵ��������
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
/// �ж�һ���ִ��Ƿ��ǻ���
/// ͬʱ���ַ���ͷβ��ʼ���м�ɨ���ִ�����������ַ���һ������ô����ִ�����һ�����ġ��������ַ����Ļ�������ֻ��Ҫά��ͷ����β������ɨ��ָ�뼴�ɡ�
/// ����ջ�Ļ���ֻ��Ҫ���ַ���ȫ��ѹ��ջ��Ȼ�����ν����ַ���ջ�������õ��ľ���ԭ�ַ��������ô����ֱ��ԭ�ַ��������ַ��Ƚϣ��Ϳ����ж���
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
/// �ж��ַ�����
/// ���������ֱ�����ĸ��ɵ��ַ���A���ַ���B���ַ���B�ĳ��ȱ��ַ���A�̡����ʣ���������ж��ַ���B��������ĸ�Ƿ����ַ���A�
/// ���ַ���A����λ���㣨26bit������ʾ)�����һ����ǩ����������B�е��ַ���A������в��ҡ�
/// ����õķ�������ʱ�临�Ӷ�O(n + m)���ռ临�Ӷ�O(1)
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
