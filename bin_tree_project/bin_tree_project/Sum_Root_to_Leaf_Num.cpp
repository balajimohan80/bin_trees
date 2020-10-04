#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<queue>

//https://leetcode.com/problems/sum-root-to-leaf-numbers/

/*
Given a binary tree containing digits from 0-9 only,
each root-to-leaf path could represent a number.
An example is the root-to-leaf path 1->2->3 which represents the number 123.
Find the total sum of all root-to-leaf numbers.

Example 1:

Input: [1,2,3]
	1
   / \
  2   3
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.

Example 2:

Input: [4,9,0,5,1]
	4
   / \
  9   0
 / \
5   1
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.

*/

class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v = 0) :val(v), left(nullptr), right(nullptr) {};
};


#if 0
//Stack based approach
int sumNumbers(TreeNode* root) {
	std::stack<TreeNode*> st;
	unsigned int res = 0;
	unsigned int prod = 0;
	unsigned int left_over = 0;
	while (!st.empty() || root) {
		while (root) {
			if (root) st.push(root);
			prod = (prod * 10) + root->val;
			root = root->left;
		}
		root = st.top(); 
		st.pop();
		if (root->left == nullptr && root->right == nullptr) {
			res += prod;
			prod /= 10;
		}
		else if(st.empty()) {
			left_over = (left_over * 10) + root->val;
			prod = left_over;
		}
	
		root = root->right;

	}
	return res;
}
#endif
int sumNumbers(TreeNode* root) {
	using Data_Type = std::pair< TreeNode*, int>;
	std::stack<Data_Type> st;
	int result = 0;
	int compute_Sum = 0;
	while (!st.empty() || root) {
		while (root) {
			compute_Sum = (compute_Sum * 10) + root->val;
			st.push(Data_Type { root, compute_Sum });
			root = root->left;
		}

		Data_Type& temp = st.top();
		if (temp.first->left == nullptr && temp.first->right == nullptr) {
			result += temp.second;
		}
		compute_Sum = temp.second;
		root = temp.first->right;
		st.pop();
	}
	return result;
}


TreeNode* create_Tree(const std::vector<std::string>& str) {
	if (!str.size()) return nullptr;
	TreeNode* head = new TreeNode(std::atoi(str[0].c_str()));
	std::queue<TreeNode*> q;
	q.push(head);
	size_t i = 1;
	while (i < str.size() && !q.empty()) {
		TreeNode* curr = q.front();
		q.pop();
		const std::string& temp_str = str[i++];
		curr->left = temp_str == "null" ? nullptr : new TreeNode(std::atoi(temp_str.c_str()));

		if (i < str.size()) {
			const std::string& r_str = str[i++];
			curr->right = r_str == "null" ? nullptr : new TreeNode(std::atoi(r_str.c_str()));
		}

		if (curr->left)
			q.push(curr->left);
		if (curr->right)
			q.push(curr->right);

	}
	return head;
}

//Using Port_Order technique
void delete_tree(TreeNode* root) {
	std::stack<TreeNode*> st;

	while (root || !st.empty()) {
		while (root) {
			if (root->right)
				st.push(root->right);
			st.push(root);
			root = root->left;
		}
		root = st.top();
		st.pop();

		if (!st.empty() && root->right == st.top()) {
			st.pop();
			st.push(root);
			root = root->right;
		}
		else {
			std::cout << "Deleting node: " << root->val << "\n";
			delete root;
			root = nullptr;
		}
	}
}


std::vector<std::string> parse(std::string& s) {
	std::vector<std::string> str;
	if (!s.length()) return str;

	int offset = 0;
	while (offset < s.length()) {
		int new_offset = s.find(',', offset);
		//This Wrapping condition used when end of the character reached
		//it returns -1.
		//Example: "A,B,C", after reached 'C', there are no "," delimeter
		//In that particular case, it retuns -1
		new_offset = (new_offset < 0) ? s.length() : new_offset;
		std::string node = s.substr(offset, new_offset - offset);
		str.push_back(node);
		offset = new_offset + 1;
	}
	return str;
}

int main() {
	//std::string in = { "3,9,2,null,null,1,7" };
	std::string in = { "1,2,3" };
	//std::string in = { "4,9,0,5,1" };
	//std::string in = { "6,8,null,7,3,null,8" };
	std::vector<std::string> v = parse(in);
	TreeNode* root = create_Tree(v);
	std::cout << "SUM_Val: " << sumNumbers(root) << "\n";
	delete_tree(root);
	return 0;
}

