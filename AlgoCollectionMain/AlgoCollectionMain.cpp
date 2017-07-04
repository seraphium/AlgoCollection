// AlgoCollectionMain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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
/// 单词翻转。输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变，句子中单词以空格符隔开。
/// 为简单起见，标点符号和普通字母一样处理。例如，输入“I am a student.”，则输出“student. a am I”。
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


int _tmain(int argc, _TCHAR* argv[])
{
	char testString[] = "teststring";
	leftRotateString(testString, strlen(testString), 4);
	char testSentence[] = "I'm still     working here";
	revertWordInString(testSentence, strlen(testSentence));

	return 0;
}
