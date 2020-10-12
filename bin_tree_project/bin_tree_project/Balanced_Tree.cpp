#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<string>
#include<tuple>

//frequent
//practice again

//https://leetcode.com/problems/balanced-binary-tree/

/*
Given a binary tree, determine if it is height-balanced.
For this problem, a height-balanced binary tree is defined as:
a binary tree in which the left and right subtrees of every node differ in height by no more than 1.
*/

class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v = 0) :val(v), left(nullptr), right(nullptr) {};
};

template<typename T>
T max(T& a, T& b) {
	return a > b ? a : b;
}

#if 0
bool identify_Balances(TreeNode* root, int& height) {
	if (root == nullptr) {
		height = -1;
		return true;
	}

	int left_height;
	int right_height;

	if (identify_Balances(root->left, left_height) &&
		identify_Balances(root->right, right_height)) {
		if (std::abs(left_height - right_height) < 2) {
			height = max(left_height, right_height)+1;
			return true;
		}
	}
	return false;
}
#else
int inline max(int a, int b) {
	return a > b ? a : b;
}

bool identify_Balances(TreeNode* root) {
	using Stack_Data_T = std::tuple<TreeNode*, int, int>;
	std::stack<Stack_Data_T> st;

	while (!st.empty() || root) {
		while (root) {
			if (root->right) {
				st.emplace(Stack_Data_T{root->right, 0, 0});
			}
			st.emplace(Stack_Data_T{ root, 0, 0 });
			root = root->left;
		}
		Stack_Data_T temp = st.top();
		st.pop();
		root = std::get<0>(temp);
		if (!st.empty() && std::get<0>(st.top()) == root->right) {
			st.pop();
			st.emplace(temp);
			root = root->right;
		}
		else {
			if (std::abs(std::get<1>(temp) - std::get<2>(temp)) < 2) {
				if (!st.empty() && std::get<0>(st.top())->left == root) {
					std::get<1>(st.top()) = max(std::get<1>(temp), std::get<2>(temp)) + 1;
				}
				else if (!st.empty() && std::get<0>(st.top())->right == root) {
					std::get<2>(st.top()) = max(std::get<1>(temp), std::get<2>(temp)) + 1;
				}
			}
			else {
				return false;
			}
			root = nullptr;
		}
	}
	return true;
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
	//std::string in = "3,9,20,null,null,15,7";
	std::string in = "1,2,2,3,3,null,null,4,4";
	std::vector<std::string> tree = parse(in);
	TreeNode* Root = create_Tree(tree);
#if 0
	int height = 0;
	std::cout << "Balanced: " << identify_Balances(Root, height) << "\n";
#else
	std::cout << "Balanced: " << identify_Balances(Root) << "\n";
#endif
	delete_tree(Root);
	return 0;
}