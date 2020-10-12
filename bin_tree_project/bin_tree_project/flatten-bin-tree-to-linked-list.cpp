#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<queue>

//frequent
//practice again
//https://leetcode.com/problems/flatten-binary-tree-to-linked-list/

/*
Given a binary tree, flatten it to a linked list in-place.

For example, given the following tree:

	1
   / \
  2   5
 / \   \
3   4   6
The flattened tree should look like:

1
 \
  2
   \
	3
	 \
	  4
	   \
		5
		 \
		  6
*/



class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v = 0) :val(v), left(nullptr), right(nullptr) {};
};


//Stack based approach
void flattend(TreeNode* root) {
	std::stack<TreeNode*> st;
	while (root) {
		if (root->left) {
			if (root->right) st.emplace(root->right);
			root->right = root->left;
			root->left = nullptr;
		}
		else if (root->left == nullptr && root->right == nullptr) {
			if (st.empty()) return;
			root->right = st.top();
			st.pop();
		}
		root = root->right;
	}
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

#include<bitset>

int main() {
	//std::string in = { "3,9,20,null,null,15,7" };
	std::string in = { "1,2,5,3,4,null,6" };
	std::vector<std::string> v = parse(in);
	TreeNode* root = create_Tree(v);
	flattend(root);
	delete_tree(root);
	return 0;
}

