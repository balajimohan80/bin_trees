#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<queue>

//frequent
//https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

/*
Serialization is the process of converting a data structure or object 
into a sequence of bits so that it can be stored in a file or memory buffer, 
or transmitted across a network connection link to be 
reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. 
There is no restriction on how your serialization/deserialization algorithm should work. 
You just need to ensure that a binary tree can be serialized to a 
string and this string can be deserialized to the original tree structure.

*/

class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v = 0) :val(v), left(nullptr), right(nullptr) {};
};


//Stack based approach
class Codec {
public:

	bool check_last_str(std::string& str, const std::string& cmp_str) {
		return str.substr(str.length() - cmp_str.length(), cmp_str.length()) == cmp_str ? true : false;
	}

	// Encodes a tree to a single string.
	std::string serialize(TreeNode* root) {
		std::string res;
		if (!root) return res;
		std::queue<TreeNode*> q;
		q.push(root);
		res += std::to_string(root->val);
		while (!q.empty()) {	
			root = q.front();
			q.pop();
			if (root->left) {
				res += "," + std::to_string(root->left->val);
				q.emplace(root->left);
			}
			else if (!q.empty() || root->right) {
				res += ",null";
			}

			if (root->right) {
				res += "," + std::to_string(root->right->val);
				q.emplace(root->right);
			}
			else if (!q.empty()) {
				res += ",null";
			}
		}
		const std::string cmp_str = ",null";
		while (res.length() > cmp_str.length() && check_last_str(res, cmp_str)) {
			res = res.substr(0, res.length() - cmp_str.length());
		}
		return res;
	}

	using Ret_Str = std::pair<int, std::string>;
	Ret_Str parse_str(std::string& data, int curr_pos, char parse_chr) {
		Ret_Str res;
		res.first = data.find(parse_chr, curr_pos);
		if (curr_pos > data.length()) {
			res.second = std::string("");
			
		}
		else if (res.first > curr_pos) {
			res.second = data.substr(curr_pos, res.first - curr_pos);
		}
		else {
			res.second = data.substr(curr_pos, data.length() - curr_pos);
			res.first = data.length() + 1;
		}
		return res;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(std::string& data) {
		TreeNode* root = nullptr;
		if (!data.length()) return root;
		std::queue<TreeNode*> q;
		Ret_Str res = parse_str(data, 0, ',');
		int curr_pos = res.first;
		root = new TreeNode(std::stoi(res.second));
		q.emplace(root);
		while (curr_pos < data.length() && !q.empty()) {
			TreeNode* temp_Node = q.front();
			q.pop();
			res = parse_str(data, curr_pos + 1, ',');
			curr_pos = res.first;
			if (res.second.length() > 0 && res.second != "null") {
				temp_Node->left = new TreeNode(std::stoi(res.second));
				q.emplace(temp_Node->left);
			}
			res = parse_str(data, curr_pos + 1, ',');
			curr_pos = res.first;
			if (res.second.length() > 0 && res.second != "null") {
				temp_Node->right = new TreeNode(std::stoi(res.second));
				q.emplace(temp_Node->right);
			}

		}
		return root;
	}
};
using Ret_Str = std::pair<int, std::string>;
Ret_Str parse_str(std::string& data, int curr_pos, char parse_chr) {
	Ret_Str res;
	res.first = data.find(parse_chr, curr_pos);
	if (curr_pos > data.length()) {
		res.second = std::string("");
	}
	else if (res.first > curr_pos) {
		res.second = data.substr(curr_pos, res.first - curr_pos);
	}
	else {
		res.second = data.substr(curr_pos, data.length() - curr_pos);
		res.first = data.length() + 1;
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
//	std::string in = { "3,9,20,null,null,15,7" };
//	std::string in = { "1,2,3,null,null,4,5" };
//	std::string in = { "1,null,2" };
//	std::string in = { "1" };
	std::string in = {"4,-7,-3,null,null,-9,-3,9,-7,-4,null,6,null,-6,-6,null,null,0,6,5,null,9,null,null,-1,-4,null,null,null,-2"};
	Codec c;

#if 0
	std::vector<std::string> v = parse(in);
	TreeNode* root = create_Tree(v);
#else
	TreeNode* root =  c.deserialize(in);
#endif
	std::string res = c.serialize(root);
	std::cout << "After Serialize: " << res << "\n";
	delete_tree(root);
	return 0;
}

