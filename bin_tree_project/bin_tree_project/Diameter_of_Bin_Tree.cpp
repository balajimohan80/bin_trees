#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<queue>
#include<tuple>

class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v = 0) :val(v), left(nullptr), right(nullptr) {};
};



//frequent
//impressed
//practice again
//https://leetcode.com/problems/diameter-of-binary-tree/

/*
Given a binary tree, you need to compute the length of the diameter of the tree. 
The diameter of a binary tree is the length of the longest path between any two nodes in a tree. 
This path may or may not pass through the root.

Example:
Given a binary tree
		  1
		 / \
		2   3
	   / \
	  4   5
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

Note: The length of path between two nodes is represented by the number of edges between them.
*/


//Stack based approach
#if 0
#define max(a,b) a > b ? a : b;
int diameterOfBinaryTree(TreeNode* root) {
	using LR_Height = std::pair<int, int>;
	using Node_Height = std::pair<TreeNode*, LR_Height>;
	if (!root) return 0;

	std::stack<Node_Height> st;
	int height = 0;

	while (!st.empty() || root) {
		while (root) {
			if (root->right) {
				st.emplace(Node_Height{ root->right, {0,0} });
			}
			st.emplace(Node_Height{ root, {0,0} });
			root = root->left;
		}

		Node_Height temp = st.top();
		st.pop();
		root = temp.first;
		if (!st.empty() && st.top().first == root->right) {
			Node_Height t1 = st.top();
			st.pop();
			st.emplace(temp);
			root = t1.first;
		}
		else {
			height = max(height, temp.second.first + temp.second.second + 1);
			if (!st.empty()) {
				if (st.top().first->left == root) {
					Node_Height& tmp = st.top();
					tmp.second.first = max(temp.second.first , temp.second.second) + 1;
				}
				else {
					Node_Height& tmp = st.top();
					tmp.second.second = max(temp.second.first , temp.second.second) + 1;
				}
			}
			root = nullptr;
		}

	}
	return height;

}
#else
int inline max(int a, int b) {
	return a > b ? a : b;
}

int diameterOfBinaryTree(TreeNode* root) {
	using Stack_Data_t = std::tuple< TreeNode*, int, int>;
	std::stack<Stack_Data_t> st;

	int max_data = 0;
	while (!st.empty() || root) {
		while (root) {
			if (root->right) {
				st.emplace(Stack_Data_t{root->right,0,0});
			}
			st.emplace(Stack_Data_t{ root, 0, 0 });
			root = root->left;
		}

		Stack_Data_t temp = st.top();
		st.pop();
		root = std::get<0>(temp);
		if (!st.empty() && root->right == std::get<0>(st.top())) {
			st.pop();
			st.emplace(temp);
			root = root->right;
		}
		else {
			max_data = max(max_data, std::get<1>(temp) + std::get<2>(temp));
			if (!st.empty() && root == std::get<0>(st.top())->left) {
				std::get<1>(st.top()) = max(std::get<1>(temp) , std::get<2>(temp)) + 1;
			}
			if (!st.empty() && root == std::get<0>(st.top())->right) {
				std::get<2>(st.top()) = max(std::get<1>(temp) , std::get<2>(temp)) + 1;
			}
			root = nullptr;
		}
	}
	return max_data;
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
	std::string in = { "1,2,3,4,5" };
	std::vector<std::string> v = parse(in);
	TreeNode* root = create_Tree(v);
	std::cout << "Diameter: " << diameterOfBinaryTree(root) << "\n";
	delete_tree(root);
	return 0;
}

