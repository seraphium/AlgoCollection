// AlgoCollectionMain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <stack>

using namespace std;


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
	while(isspace(*str))
		++str;

	//handle sign
	int sign = 1;
	if (*str == '+' || *str == '-')
	{
		if(*str == '-')
			sign = -1;
		++str;
	}

	while(isdigit(*str))
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


/// <summary>
/// ������������n��sum��������1��2��3.......n ������ȡ��������ʹ��͵���sum��Ҫ���������еĿ�������г�����
/// ע�⵽ȡn���Ͳ�ȡn�����𼴿ɣ������Ƿ�ȡ��n�����Ĳ��ԣ�����ת��Ϊһ��ֻ��ǰn-1������ص����⡣
/// </summary>
/// <param name="sum">The sum.</param>
/// <param name="n">The n.</param>
void sumOfKNumber(int sum, int n){
	static list<int> list1;
	if (n <= 0 || sum <= 0){
		return;
	}
	if (sum == n) {
		list1.reverse();
		for (list<int>::iterator ite = list1.begin();  ite != list1.end(); ite++) {
			cout << *ite << "+";
		}
		cout << n << endl;
	}
	list1.push_front(n);
	sumOfKNumber(sum - n, n - 1);
	list1.pop_front();
	sumOfKNumber(sum, n - 1);

}


/// <summary>
/// ����һ���������飬������������Ҳ�и�����
/// ������������һ�������������һ�������飬ÿ�������鶼��һ���͡� ������������ĺ͵����ֵ��Ҫ��ʱ�临�Ӷ�ΪO(n)��
/// �Ե�j+1��Ԫ��������ѡ��Ҫô����ǰ���ҵ��������飬Ҫô��Ϊ��������ĵ�һ��Ԫ�أ�
/// ���currSum���ϵ�ǰԪ��a[j]��С��a[j]������currSum����a[j]������currSum���¸�ֵ����Ϊ��һ��Ԫ�أ���currSum = a[j]��
/// ͬʱ����currSum > maxSum�������maxSum = currSum�����򱣳�ԭֵ�������¡�
/// </summary>
/// <param name="a">a.</param>
/// <param name="n">The n.</param>
/// <returns></returns>
int MaxSubArray(int*a,  int n) {
	int curSum = 0;
	int maxSum = a[0];
	for (int j = 0; j < n; j++) {
		curSum = (a[j] > curSum + a[j])? a[j]: (curSum + a[j]);
		maxSum = (maxSum > curSum)? maxSum : curSum;
	}
	return maxSum;
}


/// <summary>
/// Fibonacci���о���ݹ�ⷨ
/// �����չ������̨�ף�
///         / 1                                      n = 1
/// f(n)=     2                                      n = 2
///           4                                      n = 3       //111, 12, 21, 3
///         \ f(n-1)+f(n-2)+f(n-3)                   n > 3
/// </summary>
/// <param name="n">The n.</param>
/// <returns></returns>
long long fibonacci(unsigned int n) {
	int result[3] = {0, 1, 2};
	if  (n < 3){
		return result[n];
	}
	return fibonacci(n - 1) + fibonacci(n - 2);
}


/// <summary>
/// һ��̨���ܹ���n �������һ�ο�����1 ����Ҳ������2 ��
/// �ⷨһ�õĵݹ�ķ���������ظ�����Ĺ�������ʵ�ϣ����ǿ��ԴӺ���ǰ�ƣ�һ��������֮ǰ����Ľ�����ơ�
/// ��ʼ��ʱ��dp[0]=dp[1]=1��Ȼ����Ƽ��㼴�ɣ�dp[n] = dp[n-1] + dp[n-2]��
/// </summary>
/// <param name="n">The n.</param>
/// <returns></returns>
int climbStairs(int n) {
	int dp[3] = {1, 1};
	if (n < 2) {
		return 1;
	}
	for (int i = 2; i < n; i++)  {
		dp[2] = dp[0] +  dp[1];
		dp[0] = dp[1];
		dp[1] = dp[2];
	}
	return dp[2];
}

/// <summary>
///  ��һ�100ԪǮ����1,2,5,10����Ǯ�����ܹ��ж��ٶһ�������
/// ��������
/// </summary>
void changeCoin(){
	const int N = 100;
	int dimes[] = { 1, 2, 5, 10 };
	int arr[N + 1] = { 1 };
	for (int i = 0; i < sizeof(dimes) / sizeof(int); ++i)
	{
		for (int j = dimes[i]; j <= N; ++j)
		{
			arr[j] += arr[j - dimes[i]];
		}
	}

}

/// <summary>
///  determine if number is odd or not
/// </summary>
/// <param name="data">The data.</param>
/// <returns></returns>
bool isOdd(int data) {
	return data & 1 == 1;
}


/// <summary>
/// ����һ���������飬�������������ֵ�˳��ʹ����������λ�������ǰ�벿�֣�����ż��λ������ĺ�벿�֡�Ҫ��ʱ�临�Ӷ�ΪO(n)��
/// ���partition��ʵ��һ�����ǿ��Կ���ά������ָ�룬һ��ָ��ָ������ĵ�һ�����֣����ǳ�֮Ϊͷָ�룬�����ƶ���һ��ָ��ָ�����һ�����֣���֮Ϊβָ�룬�����ƶ���
/// </summary>
/// <param name="pData">The p data.</param>
/// <param name="length">The length.</param>
void OddEvenSort(int* pData, unsigned int length)  {
	if (pData == NULL || length == 0) {
		return;
	}

	int* pBegin = pData;
	int* pEnd = pData + length - 1;

	while (pBegin < pEnd) {
		if (isOdd(*pBegin)) {
			pBegin++;
		}
		else if (!isOdd(*pEnd)) {
			pEnd--;
		}
		else {
			swap(*pBegin, *pEnd);
		}
	}
}


/// <summary>
/// ���partition������ʵ�֣�����Ҳ����ά������ָ��i��j
/// һ��ָ��ָ������ĵ�һ������ǰһ��λ�ã����ǳ�֮Ϊ��ָ��i�������ƶ���
/// һ��ָ��ָ�������һ��������֮Ϊǰָ��j��Ҳ�����ƶ�����ǰָ��j�������ƶ���
/// ���ǰָ��jָ�������������������iָ�������ƶ�һλ��Ȼ�󽻻�i��jָ��������ָ������֡�
/// </summary>
/// <param name="data">The data.</param>
/// <param name="lo">The lo.</param>
/// <param name="hi">The hi.</param>
void OddEvenSort2(int* data, int lo, int hi){
	int i = lo - 1;
	for(int j = lo; j < hi; j++) {
		if (isOdd(data[j])) {
			i += 1;
			swap(data[i], data[j]);
		}
		

	}
	swap(data[i+1], data[hi]);
}


/// <summary>
/// ��������һ�����ֳ��ֵĴ������������鳤�ȵ�һ�룬�ҳ�������֡�
///���ǿ����ڱ��������ʱ�򱣴�����ֵ��һ��candidate���������������б�������ĳ�����֣�һ��nTimes����ʾ��ǰ���ֵĳ��ִ��������У�nTimes��ʼ��Ϊ1�������Ǳ�������������һ�����ֵ�ʱ��
///�����һ��������֮ǰcandidate�����������ͬ����nTimes��1��
///�����һ��������֮ǰcandidate��������ֲ�ͬ����nTimes��1��
///ÿ�����ִ���nTimes��Ϊ0����candidate������һ�����֣�����nTimes������Ϊ1�� ֱ�������������е���������Ϊֹ��
/// </summary>
/// <param name="a">a.</param>
/// <param name="n">The n.</param>
/// <returns></returns>
int FindOverHalfNumber(int* a, int n) {
	int candidate = a[0];
	int number = 1;
	for (int i = 1; i < n; i++) {
		if (number == 0){
			candidate = a[i];
			number = 1;
		} else {
			if (candidate == a[i]) {
				number++;
			} else {
				number--;
			}
		} 
	}
	return candidate;

}

/// <summary>
/// ��һ�����������У�ȡ���˻������Ӵ���ֵ������ -2.5��4��0��3��0.5��8��-1��
/// ��ȡ�������˻������Ӵ�Ϊ3��0.5��8��Ҳ����˵�����������У�3 0.5 8��3�����ĳ˻�30.58=12�����ģ�������������
/// �����ⷨ������forѭ��ֱ����ѯ
/// </summary>
/// <param name="a">a.</param>
/// <param name="n">The n.</param>
/// <returns></returns>
double maxProductSubstringBrute(double* a, int n)  {
	double maxResult = a[0];
	for (int i = 0; i < n; i++) {
		double x = 1;
		for (int j = i; j < n; j++){
			x *= a[j];
			if (x >  maxResult) {
				maxResult = x;
			}
		}
	}
	return maxResult;
}

/// <summary>
/// ��һ�����������У�ȡ���˻������Ӵ���ֵ������ -2.5��4��0��3��0.5��8��-1��
/// ֱ�����ö�̬�滮����⣬���ǵ����ܴ��ڸ��������
/// ������maxend����ʾ��a[i]��β����������Ӵ��ĳ˻�ֵ����minend��ʾ��a[i]��β����С���Ӵ��ĳ˻�ֵ����ô״̬ת�Ʒ���Ϊ
/// maxend = max(max(maxend * a[i], minend * a[i]), a[i]);
/// minend = min(min(maxend * a[i], minend * a[i]), a[i]);  
/// </summary>
/// <param name="a">a.</param>
/// <param name="n">The n.</param>
/// <returns></returns>
double maxProductDynamic(double* a, int n) {
	double maxEnd=a[0];
	double minEnd=a[0];
	double maxResult = a[0];
	for (int i = 1; i < n; i++) {
		double end1 = maxEnd * a[i], end2 = minEnd * a[i];
		maxEnd = max(max(end1,  end2), a[i]);
		minEnd = min(min(end1, end2), a[i]);
		maxResult = max(maxResult, maxEnd);
	}
	return maxResult;
}



/// <summary>
/// n �����֣� 0,1,��,n-1���γ�һ��ԲȦ�������� 0 ��ʼ��
/// ÿ�δ����ԲȦ��ɾ���� m �����֣���һ��Ϊ��ǰ���ֱ����ڶ���Ϊ��ǰ���ֵ���һ��
/// ���֣���
/// ��һ������ɾ���󣬴ӱ�ɾ�����ֵ���һ������ɾ���� m �����֡�
/// ��������ԲȦ��ʣ�µ����һ������
/// Google solution
/// 1) if we shift the ids by k, namely, start from k instead of 0, we should add the result by k%n
/// 2) after the first round, we start from k+1 ( possibly % n) with n-1 elements, that is equal to
// an (n-1) problem while start from (k+1)th element instead of 0, so the answer is (f(n-1,m)+k+1)%n
/// 3) k = m-1, so f(n,m)=(f(n-1,m)+m)%n.
/// finally, f(1, m) = 0;
/// </summary>
/// <param name="n">The n.</param>
/// <param name="m">The m.</param>
/// <returns></returns>
int Joseph(int n, int m) {
	int fn = 0;
	for (int i = 2; i <= n ; i++){
		fn = (fn + m) % i;
	}
	return fn;
}

struct TreeNode{
	int value;
	TreeNode* left;
	TreeNode* right;
} ;

void visit(TreeNode*  node){
	cout<<node->value<<endl;
}

/// <summary>
/// Preorder traverse bi-tree
/// Non-recursive
/// </summary>
/// <param name="node">The root node.</param>
void preorderNonrecursive(TreeNode * node) {
	stack<TreeNode *> s;
	s.push(node);
	while (!s.empty()) {
		TreeNode * n = s.top();
		s.pop();
		visit(n);
		if (n->right!=NULL) s.push(n->right);
		if (n->left!=NULL) s.push(n->left);
	}
}

/// <summary>
/// In-order traverse bi-tree
/// Non-recursive
/// </summary>
/// <param name="node">The root node.</param>
void inorderNonrecursive(TreeNode * node) {
	stack<TreeNode *> s;
	TreeNode * current = node;
	while (!s.empty() || current != NULL) {
		if (current != NULL) {
			s.push(current);
			current = current->left;
		} else {
			current = s.top();
			s.pop();
			visit(current);
			current = current->right;
		}
	}
}

/// <summary>
/// Post-order traverse bi-tree
/// Non-recursive
/// the node first traversed is the node last visited. This recalls the feature of stack.
/// So we could use a stack to store all the nodes then pop them out altogether
/// </summary>
/// <param name="node">The root node.</param>
void postorderNonrecursive(TreeNode * node) {
	// visiting occurs only when current has no right child or last visited
	// is his right child
	stack<TreeNode *> sTraverse, sVisit;
	sTraverse.push(node);
	while (!sTraverse.empty()) {
		TreeNode * p = sTraverse.top();
		sTraverse.pop();
		sVisit.push(p);
		if (p->left != NULL) sTraverse.push(p->left);
		if (p->right != NULL) sTraverse.push(p->right);
	}
	while (!sVisit.empty()) {
		visit(sVisit.top());
		sVisit.pop();

	}
}

TreeNode* createTree(){
	TreeNode* rootNode = new TreeNode();
	rootNode->value = 0;
	TreeNode* leftNode = new TreeNode();
	leftNode->value = 1;
	TreeNode* rightNode = new TreeNode();
	rightNode->value = 2;
	rootNode->left = leftNode;
	rootNode->right = rightNode;

	return rootNode;
}
	

int main(int argc, char* argv[])
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

	sumOfKNumber(5, 10);

	int numClimbs = climbStairs(10);

	changeCoin();

	int oldeven[] = {1,5,4,2,6,3};
	OddEvenSort(oldeven, 6);

	int oldeven2[] = {1,4,8,3,7,9};
	OddEvenSort2(oldeven2, 0, 5);

	int overhalfarray[] = {1,2,2,2,2,4,5};
	int overhalf = FindOverHalfNumber(overhalfarray, 7);

	double maxArray[] = {-2.5, 5, 0, 3, 0.5, 8, -1};
	double maxMulti = maxProductSubstringBrute(maxArray, 7);
	double maxDynamic = maxProductDynamic(maxArray, 7);

	TreeNode* pNode = createTree();
	//preorderNonrecursive(pNode);
	//inorderNonrecursive(pNode);
	postorderNonrecursive(pNode);
	return 0;
}
