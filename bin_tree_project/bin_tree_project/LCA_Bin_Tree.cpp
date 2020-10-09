#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<queue>
#include<tuple>

//https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

/*
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
According to the definition of LCA on Wikipedia: 
“The lowest common ancestor is defined between two nodes p and q as the lowest node in T 
that has both p and q as descendants (where we allow a node to be a descendant of itself).”

Given the following binary tree:  root = [3,5,1,6,2,0,8,null,null,7,4]


Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.
Example 2:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

*/

class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v = 0) :val(v), left(nullptr), right(nullptr) {};
};


//Stack based approach
#if 0
//Implemented using in-order
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	using LCA_Data_t = std::tuple<TreeNode*, TreeNode*, TreeNode*>;
	std::stack<LCA_Data_t> st;

	while (!st.empty() || root) {
		while (root) {
			LCA_Data_t temp;
			std::get<0>(temp) = root;
			std::get<1>(temp) = (root->val == p->val) ? p : nullptr;
			std::get<2>(temp) = (root->val == q->val) ? q : nullptr;
			st.emplace(temp);
			root = root->left;
		}
		LCA_Data_t temp = st.top();
		st.pop();

		if (std::get<1>(temp) != nullptr && std::get<2>(temp) != nullptr) {
			return std::get<0>(temp);
		}
		else if (std::get<1>(temp) != nullptr) {
			std::get<1>(st.top()) = std::get<1>(temp);
		}
		else if (std::get<2>(temp) != nullptr) {
			std::get<2>(st.top()) = std::get<2>(temp);
		}
		root = std::get<0>(temp);
		root = root->right;
	}
	return nullptr;
}
#else
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	using Stack_Data_T = std::tuple< TreeNode*, TreeNode*, TreeNode*>;
	std::stack<Stack_Data_T> st;

	while (!st.empty() || root) {
		while (root) {
			if (root->right) {
				Stack_Data_T temp;
				std::get<0>(temp) = root->right;
				std::get<1>(temp) = root->right->val == p->val ? p : nullptr;
				std::get<2>(temp) = root->right->val == q->val ? q : nullptr;
				st.emplace(temp);
			}
			Stack_Data_T temp;
			std::get<0>(temp) = root;
			std::get<1>(temp) = root->val == p->val ? p : nullptr;
			std::get<2>(temp) = root->val == q->val ? q : nullptr;
			st.emplace(temp);
			root = root->left;
		}

		Stack_Data_T temp = st.top();
		root = std::get<0>(temp);
		st.pop();
		if (!st.empty() && std::get<0>(st.top()) == std::get<0>(temp)->right) {
			Stack_Data_T t = st.top();
			st.pop();
			st.emplace(temp);
			root = std::get<0>(t);
		}
		else {
			if (std::get<1>(temp) != nullptr && std::get<2>(temp) != nullptr) {
				return root;
			}
			else if (!st.empty() && std::get<1>(temp) != nullptr) {
				std::get<1>(st.top()) = std::get<1>(temp);
			}
			else if (!st.empty() && std::get<2>(temp) != nullptr) {
				std::get<2>(st.top()) = std::get<2>(temp);
			}
			root = nullptr;
		}
	}
	return nullptr;
}
#endif

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
	std::string in = { "3,5,1,6,2,0,8,null,null,7,4" };
	std::vector<std::string> v = parse(in);
	TreeNode* root = create_Tree(v);
	TreeNode* p = new TreeNode(7);
	TreeNode* q = new TreeNode(8);

	TreeNode* lca = lowestCommonAncestor(root, p, q);
	if (!lca)
		std::cout << "LCA: NULL\n";
	else
		std::cout << "LCA: " << lca->val << "\n";
	delete p;
	delete q;
	delete_tree(root);
	return 0;
}

