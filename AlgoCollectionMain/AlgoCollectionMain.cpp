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


/// <summary>
/// 输入两个整数n和sum，从数列1，2，3.......n 中随意取几个数，使其和等于sum，要求将其中所有的可能组合列出来。
/// 注意到取n，和不取n个区别即可，考虑是否取第n个数的策略，可以转化为一个只和前n-1个数相关的问题。
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
/// 输入一个整形数组，数组里有正数也有负数。
/// 数组中连续的一个或多个整数组成一个子数组，每个子数组都有一个和。 求所有子数组的和的最大值，要求时间复杂度为O(n)。
/// 对第j+1个元素有两种选择：要么放入前面找到的子数组，要么做为新子数组的第一个元素；
/// 如果currSum加上当前元素a[j]后不小于a[j]，则令currSum加上a[j]，否则currSum重新赋值，置为下一个元素，即currSum = a[j]。
/// 同时，当currSum > maxSum，则更新maxSum = currSum，否则保持原值，不更新。
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
/// Fibonacci数列经典递归解法
/// 如果扩展到三级台阶：
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
/// 一个台阶总共有n 级，如果一次可以跳1 级，也可以跳2 级
/// 解法一用的递归的方法有许多重复计算的工作，事实上，我们可以从后往前推，一步步利用之前计算的结果递推。
/// 初始化时，dp[0]=dp[1]=1，然后递推计算即可：dp[n] = dp[n-1] + dp[n-2]。
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
///  想兑换100元钱，有1,2,5,10四种钱，问总共有多少兑换方法。
/// ？？？？
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
/// 输入一个整数数组，调整数组中数字的顺序，使得所有奇数位于数组的前半部分，所有偶数位于数组的后半部分。要求时间复杂度为O(n)。
/// 借鉴partition的实现一，我们可以考虑维护两个指针，一个指针指向数组的第一个数字，我们称之为头指针，向右移动；一个指针指向最后一个数字，称之为尾指针，向左移动。
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
/// 借鉴partition的上述实现，我们也可以维护两个指针i和j
/// 一个指针指向数组的第一个数的前一个位置，我们称之为后指针i，向右移动；
/// 一个指针指向数组第一个数，称之为前指针j，也向右移动，且前指针j先向右移动。
/// 如果前指针j指向的数字是奇数，则令i指针向右移动一位，然后交换i和j指针所各自指向的数字。
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
/// 数组中有一个数字出现的次数超过了数组长度的一半，找出这个数字。
///我们可以在遍历数组的时候保存两个值：一个candidate，用来保存数组中遍历到的某个数字；一个nTimes，表示当前数字的出现次数，其中，nTimes初始化为1。当我们遍历到数组中下一个数字的时候：
///如果下一个数字与之前candidate保存的数字相同，则nTimes加1；
///如果下一个数字与之前candidate保存的数字不同，则nTimes减1；
///每当出现次数nTimes变为0后，用candidate保存下一个数字，并把nTimes重新设为1。 直到遍历完数组中的所有数字为止。
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
/// 给一个浮点数序列，取最大乘积连续子串的值，例如 -2.5，4，0，3，0.5，8，-1，
/// 则取出的最大乘积连续子串为3，0.5，8。也就是说，上述数组中，3 0.5 8这3个数的乘积30.58=12是最大的，而且是连续的
/// 暴力解法，两个for循环直接轮询
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
/// 给一个浮点数序列，取最大乘积连续子串的值，例如 -2.5，4，0，3，0.5，8，-1，
/// 直接利用动态规划来求解，考虑到可能存在负数的情况
/// 我们用maxend来表示以a[i]结尾的最大连续子串的乘积值，用minend表示以a[i]结尾的最小的子串的乘积值，那么状态转移方程为
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
/// n 个数字（ 0,1,…,n-1）形成一个圆圈，从数字 0 开始，
/// 每次从这个圆圈中删除第 m 个数字（第一个为当前数字本身，第二个为当前数字的下一个
/// 数字）。
/// 当一个数字删除后，从被删除数字的下一个继续删除第 m 个数字。
/// 求出在这个圆圈中剩下的最后一个数字
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


///Get least common parent of two tree node
TreeNode* getLCA(TreeNode* root, TreeNode* x, TreeNode* y) {
	if (root == NULL){
		return root;
	}
	if (root == x || root == y){
		return root;
	}
	TreeNode* left = getLCA(root->left, x, y);
	TreeNode* right = getLCA(root->right, x, y);
	if (left == NULL){
		return right;
	}
	if (right == NULL) {
		return left;
	}
	return root;



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

//函数功能 ： 打印最长递减子序列  
//函数参数 ： pArray指向源数组，pB指向辅助数组，k表示最长子序列的末尾元素  
//返回值 ：   无  
void Print(int *pArray, int *pB, int k)  
{  
    for (int i = k - 1; i >= 0; i--)  
    {  
        if(pB[k] == pB[i] + 1 && pArray[i] > pArray[k]) //再现动态规划求解的过程，只不过是逆向  
        {  
            Print(pArray, pB, i);  
            break;  
        }  
    }  
    cout<<pArray[k]<<' ';  
}  

//函数功能 ： 一个数组的最长递减子序列  
//函数参数 ： pArray指向源数组，len表示数组长度  
//返回值 ：   无  
void FindMDS(int *pArray, int len)  
{  
    int i, j, maxi = 0;        //maxi用来记录最长递减序列的末尾元素  
    int *pB = new int [len];   //辅助空间，pB[i]表示以pAray[i]结尾的最长递减序列长度  
    for(i = 0 ; i < len; i++)  //初始化  
        pB[i] = 0;  
  
    for(i = 0; i < len; i++)   //计算以pAray[i]结尾的最长递减序列  
    {  
        pB[i] = 1;
        int maxb = 0;
        for(j = 0; j < i; j++)  
        {  
            if(pArray[j] > pArray[i] && pB[j] > maxb) //这个判断式是关键
            {
                maxb = pB[j];
            }
        }
        pB[i] = maxb + 1;
        if(pB[i] > pB[maxi]) //更新当前找到的最长递减序列
            maxi = i;
    }  
    Print(pArray, pB, maxi); //打印目标序列  
    delete [] pB;  
}


///函数功能 ： 递归返回数组p从begin到end之间的全排列
void permHelper(int* p, int begin, int end){
	if (begin == end)
	{
		//output result
		for (int i = 0; i < end; i++){
			cout<<p[i]<<" ";
		}
		cout<<endl;
	}
	for (int j = begin; j < end; j++){
		swap(p[begin],p[j]);
		permHelper(p, begin + 1, end);
		swap(p[begin], p[j]);
	}


}

void fullPermutation(int* p, int n){
	if (p == NULL || n <= 0) {
		return;
	}
	permHelper(p, 0, n);
}

//definition of link node
struct LinkNode {
	int value;
	LinkNode* next;
};

//code to create sample linked list
LinkNode* createLink()
{
	LinkNode* pHead = new LinkNode();
	pHead->value = 0;
	LinkNode* p2 = new LinkNode();
	p2->value = 1;
	LinkNode* p3 = new LinkNode();
	p3->value = 2;
	pHead->next = p2;
	p2->next = p3;

	return pHead;
}


///reverse linked list using recursive method
LinkNode* reverseLink(LinkNode* p){

	if (p == NULL || p->next == NULL){
		return p;
	}
	LinkNode* pMid = p->next;
	LinkNode* pPrevious = reverseLink(pMid);
	pMid->next = p;
	p -> next = NULL;
	return pPrevious;
}

///reverse linked list using non-recursive method
LinkNode* reverseLinkNonRecursive(LinkNode* head){
	if (head == NULL) {
		return head;
	}
	LinkNode* previous = NULL;
	LinkNode* p = head;
	LinkNode* next = NULL;
	while (p != NULL){
		next = p->next;
		p->next = previous;
		previous = p;
		p = next;
	}

	return previous;
}

///delete node in linked list
///Copy the data from tobedeleted’s next to tobedeleted. then delete tobedeleted.
///The special case is tobedelete is the tail, then we must iterate to find its predecessor.
///The amortized time complexity is O(1).

void deleteLinkNode(LinkNode* pHead, LinkNode* pDelete){
	if (pHead == NULL){
		return;
	}
	if (pDelete -> next == NULL){
		//special case, need to iterate to previous node
		LinkNode* p = pHead;
		while (p->next != NULL && p->next != pDelete)
			p = p->next;
		p ->next = NULL;
		delete pDelete;
		return;
	}
	LinkNode* pRealDelete = pDelete->next;
	pDelete->value = pRealDelete->value;
	pDelete->next = pRealDelete->next;
	delete pRealDelete;

}


///recursively put item into stack bottom
void putToBottom(std::stack<int>& stack, int object) {
	if (stack.empty()){
		stack.push(object);
		return;
	}
	int obj = stack.top();
	stack.pop();
	putToBottom(stack, object);
	stack.push(obj);

}

///recursively reverse stack items
void revertStack(std::stack<int>& stack){
	if (stack.size() <= 1){
		return;
	}
	int obj = stack.top();
	stack.pop();
	revertStack(stack);
	putToBottom(stack, obj);
}


///display stack items from top
///will destroy stack
void PrintStackFromTop(std::stack<int> stack){

	while (!stack.empty()) {
		int top = stack.top();
		cout<<top<<endl;
		stack.pop();
	}
}



///get exponent calculation using recursion
double power(double base, int exp) {
	if (exp == 1) return base;
	double half = power(base, exp >> 1);
	return (((exp & 1) == 1) ? base : 1.0) * half * half;
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

	int decrease[] = {9, 4, 3, 2, 5, 4, 3, 2};
	FindMDS(decrease, sizeof(decrease)/sizeof(int));

	int perm[] = {1,2,3};
	fullPermutation(perm, 3);

	LinkNode* pHead = createLink();
	//LinkNode* pReversedHead = reverseLink(pHead);
	//LinkNode* pReversedHead = reverseLinkNonRecursive(pHead);
	LinkNode* pDelete = pHead->next->next;
	deleteLinkNode(pHead, pDelete);

	stack<int> stack;
	stack.push(1);
	stack.push(2);
	stack.push(3);

	revertStack(stack);
	PrintStackFromTop(stack);

	int res = power(100, 2);

	return 0;
}
