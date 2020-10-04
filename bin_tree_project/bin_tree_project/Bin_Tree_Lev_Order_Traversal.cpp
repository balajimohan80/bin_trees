#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<queue>


//Frequent
//practice again
//https://leetcode.com/problems/binary-tree-level-order-traversal-ii/

//Please refer
//https://www.youtube.com/watch?v=NjdOhYKjFrU&ab_channel=VivekanandKhyade-AlgorithmEveryDay

/*
Given a binary tree, return the bottom-up level order traversal of its nodes' values.
(ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],
	3
   / \
  9  20
	/  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7],
  [9,20],
  [3]
]
*/

class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v = 0) :val(v), left(nullptr), right(nullptr) {};
};


//Level Order Traversal
//Solution-1
std::vector<std::vector<int>> printlevel_Order_Sol_1(TreeNode* root) {
	std::queue<TreeNode*> q;
	std::vector<std::vector<int>> res;
	q.push(root);
	q.push(nullptr);

	std::vector<int> v;
	while (!q.empty()) {
		root = q.front();
		q.pop();
		if (root) {
			v.push_back(root->val);
			if (root->left)
				q.push(root->left);
			if (root->right)
				q.push(root->right);
		}
		else {
			//reverse it
			res.emplace(res.begin(), v);
			v.clear();
			if (!q.empty())
				q.push(nullptr);
		}
	}
	return res;
}

//Sol-2
std::vector<std::vector<int>> printlevel_Order_Sol_2(TreeNode* root) {
	std::queue<TreeNode*> q;
	std::vector<std::vector<int>> res;
	q.push(root);

	while (!q.empty()) {
		std::vector<int> v;
		size_t size = q.size();

		while (size--) {
			root = q.front();
			q.pop();
			v.push_back(root->val);
			if (root->left)
				q.push(root->left);
			if (root->right)
				q.push(root->right);
		}
		res.emplace(res.begin(), v);
	}
	return res;
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
	std::string in = { "3,9,20,null,null,15,7,3,9,20 21, null, null, null, 29" };
	std::vector<std::string> v = parse(in);
	TreeNode* root = create_Tree(v);
	std::vector<std::vector<int>> ret = printlevel_Order_Sol_2(root);
	for (auto& val : ret) {
		for (auto& v : val) {
			std::cout << v << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\n";
	delete_tree(root);
	return 0;
}

