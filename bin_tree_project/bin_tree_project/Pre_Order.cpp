#include<iostream>
#include<vector>
#include<stack>
#include<string>

class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v = 0) :val(v), left(nullptr), right(nullptr) {};
};


//Stack based approach
std::vector<int> pre_Order(TreeNode* root) {
	if (!root) return {};
	std::vector<int> res;
	std::stack<TreeNode*> st;

	st.push(root);
	while (!st.empty()) {
		TreeNode* temp = st.top();
		st.pop();
		res.push_back(temp->val);
		if (temp->right)
			st.push(temp->right);
		if (temp->left)
			st.push(temp->left);
	}
	return res;
}


TreeNode* create_Tree(const std::vector<std::string>& str) {
	if (!str.size()) return nullptr;
	TreeNode* head = new TreeNode(std::atoi(str[0].c_str()));
	std::stack<TreeNode*> st;
	st.push(head);
	size_t i = 1;
	while (i < str.size() && !st.empty()) {
		TreeNode* curr = st.top();
		st.pop();
		const std::string& temp_str = str[i++];
		curr->left = temp_str == "null" ? nullptr : new TreeNode(std::atoi(temp_str.c_str()));

		if (i < str.size()) {
			const std::string& r_str = str[i++];
			curr->right = r_str == "null" ? nullptr : new TreeNode(std::atoi(r_str.c_str()));
		}

		if (curr->right)
			st.push(curr->right);
		if (curr->left)
			st.push(curr->left);
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
	std::string in = { "3,9,20,null,null,15,7" };
	std::vector<std::string> v = parse(in);
	TreeNode* root = create_Tree(v);
	std::vector<int> ret = pre_Order(root);
	for (auto& val : ret)
		std::cout << val << " ";
	std::cout << "\n";
	delete_tree(root);
	return 0;
}

