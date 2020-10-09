#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<queue>


//https://leetcode.com/problems/validate-binary-search-tree/


/*
Given a binary tree, determine if it is a valid binary search tree (BST).
Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.


Example 1:

	2
   / \
  1   3

Input: [2,1,3]
Output: true
Example 2:

	5
   / \
  1   4
	 / \
	3   6

Input: [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
*/

class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v = 0) :val(v), left(nullptr), right(nullptr) {};
};


//Stack based approach
bool isValidBST(TreeNode* root) {
	if (!root) return true;
 	std::stack< TreeNode*> st;
	int prev_Node_Val;
	while (root) {
		st.push(root);
		root = root->left;
	}
	root = st.top();
	st.pop();
	prev_Node_Val = root->val;
	root = root->right;
	while (!st.empty() || root) {
		while (root) {
			st.push(root);
			root = root->left;
		}
		root = st.top(); 
		st.pop();
		if (root->val > prev_Node_Val) {
			prev_Node_Val = root->val;
		}
		else {
			return false;
		}
		root = root->right;
	}
	
	return true;
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
	//std::string in = { "2,1,3" };
	//std::string in = { "5,1,4,null,null,3,6" };
	//std::string in = "10,5,15,null,null,6,20";
	//std::string in = { "1,1" };
	std::string in = { "-2147483648" };
	std::vector<std::string> v = parse(in);
	TreeNode* root = create_Tree(v);
	std::cout << "ValidBST: " << isValidBST(root) << "\n";
	delete_tree(root);
	return 0;
}

