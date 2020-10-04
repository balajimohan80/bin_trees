#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<queue>
#include<map>

//frequent
//Practice again
//impressed


class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v = 0) :val(v), left(nullptr), right(nullptr) {};
};


std::vector<std::vector<int>> verticalTraversal(TreeNode* root) {
	if (!root) return {};
	using Data_t = std::pair< TreeNode*, int>;
	using Level_Height = int;
	using Node_Val = int;
	using Level_Node = std::pair<Level_Height, Node_Val>;
	std::queue<Data_t> q;
	std::map<int, std::vector<Level_Node>> u_Map;

	q.push(Data_t{ root, 1 });
	u_Map[1].push_back(Level_Node{1, root->val });
	Level_Height ct=1;
	while (!q.empty()) {
		Data_t temp = q.front();
		q.pop();
		ct++;
		if (temp.first->left) {
			u_Map[temp.second - 1].push_back(Level_Node{ct, temp.first->left->val });
			q.push(Data_t{ temp.first->left, temp.second - 1 });
		}

		if (temp.first->right) {
			u_Map[temp.second + 1].push_back(Level_Node{ ct,temp.first->right->val });
			q.push(Data_t{ temp.first->right, temp.second + 1 });
		}
		
	}

	std::vector<std::vector<int>> ret;
	auto it = u_Map.begin();
	while (it != u_Map.end()) {
#if 0
		std::sort(it->second.begin(), it->second.end(), [](const Level_Node& a, const Level_Node& b)
			{
				return a.first == b.first ? a.second < b.second : a.first < b.first;
			});
#else
		std::sort(it->second.begin(), it->second.end());
#endif
		std::vector<int> temp;
		for (auto& val : it->second) {
			temp.push_back(val.second);
		}
		ret.push_back(temp);
		it++;
	}
	return ret;
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
	//std::string in = { "3,9,20,null,null,15,7" };
	//std::string in = { "1,2,3,4,5,6,7" };
	//std::string in = {"0,5,1,9,null,2,null,null,null,null,3,4,8,6,null,null,null,7"};
	std::string in = { "0,2,1,3,null,null,null,4,5,null,7,6,null,10,8,11,9" };
	std::vector<std::string> v = parse(in);
	TreeNode* root = create_Tree(v);
	std::vector<std::vector<int>> res = verticalTraversal(root);
	for (auto& val : res) {
		for (auto& v : val) {
			std::cout << v << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
	delete_tree(root);
	return 0;
}

