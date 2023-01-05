class Solution
{
private:

public:
    
//     this function maps every node to their parent node
    void markParent(Node* root, unordered_map<Node*, Node*>&parent){
        queue<Node*>q;
        q.push(root);
        
        while(!q.empty()){
            Node* curr = q.front();
            q.pop();
            if(curr->left){
                parent[curr->left] = curr;
                q.push(curr->left);
            }
            if(curr->right){
                parent[curr->right] = curr;
                q.push(curr->right);
            }
        }
    }
//   This function will find the node with value target
    void getTargetNode(Node* root, int target, Node* &targetNode){
        
        if(!root) return;
        if(root->data==target){
            targetNode = root;
            return;
        }
        getTargetNode(root->left, target, targetNode);
        getTargetNode(root->right, target, targetNode);
    }

    vector <int> KDistanceNodes(Node* root, int target , int k)
    {
        // return the sorted vector of all nodes at k dist
        vector<int> res;
        
        if(!root) return res;
        unordered_map<Node*, Node*> parent;
        markParent(root, parent);
        
        Node* targetNode;
        getTargetNode(root, target, targetNode);
        
        if(!targetNode) return res;
        
        unordered_map<Node*, bool> visited;
        queue<Node*> q;
        q.push(targetNode);
        visited[targetNode] = true;
        int level=0;
        
        while(!q.empty()){
            if(level==k) break;
            level++;
            int size = q.size();
            while(size--){
                Node* curr = q.front();
                q.pop();
                if(curr->left && !visited[curr->left]){
                    q.push(curr->left);
                    visited[curr->left] = true;
                }
                if(curr->right && !visited[curr->right]){
                    q.push(curr->right);
                    visited[curr->right] = true;
                }
                if(parent[curr] && !visited[parent[curr]]){
                    q.push(parent[curr]);
                    visited[parent[curr]] = true;
                }
            }
        }
        // vector<int> res;
        while(!q.empty()){
            Node* node = q.front();
            q.pop();
            res.push_back(node->data);
        }
        sort(res.begin(), res.end());
        return res;
    }
};
