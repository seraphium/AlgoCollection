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
/// ���ʷ�ת������һ��Ӣ�ľ��ӣ���ת�����е��ʵ�˳�򣬵��������ַ���˳�򲻱䣬�����е����Կո��������
/// Ϊ������������ź���ͨ��ĸһ���������磬���롰I am a student.�����������student. a am I����
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
