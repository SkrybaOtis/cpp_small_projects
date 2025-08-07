#include <iostream>
#include <vector>
#include <queue>
#include <map>

const int ALPHABET_SIZE = 26; 

struct TrieNode {
    std::map<char, TrieNode*> children;
    TrieNode *fail;
    bool isEndOfWord;
    std::string isEndOfWordLetter;

    TrieNode() : fail(nullptr), isEndOfWord(false) {}
};


class AhoCorasick {
private:
    TrieNode *root;

public:
    AhoCorasick() : root(new TrieNode()) {}
    
    void insert(const std::string &word, const std::string &letterLabel){
        TrieNode *node = root;
        for (char letter : word) {
            if (node->children.find(letter) == node->children.end()) {
                node->children[letter] = new TrieNode();
            }
            node = node->children[letter];
        }
        node->isEndOfWord = true; 
        node->isEndOfWordLetter = letterLabel;
    }

    void buildFailureLinks() {
        std::queue<TrieNode*> q;
        root->fail = root;
        for (auto &p : root->children) {
            p.second->fail = root;
            q.push(p.second);
        }

        while (!q.empty()) {
            TrieNode *current = q.front();
            q.pop();

            for (auto &p : current->children) {
                TrieNode *child = p.second;
                TrieNode *failure = current->fail;

                while (failure != root && failure->children.find(p.first) == failure->children.end()) {
                    failure = failure->fail;
                }

                if (failure->children.find(p.first) != failure->children.end()) {
                    child->fail = failure->children[p.first];
                } else {
                    child->fail = root;
                }

                if (child->fail->isEndOfWord) {
                    child->isEndOfWord = true;
                }

                q.push(child);
            }
        }
    }

    void search(const std::string &text, std::string &finded) {
        TrieNode *node = root;
        	int lastFindPosition = -1;
			int position = 0;
        for (char c : text) {
            while (node != root && node->children.find(c) == node->children.end()) {
                node = node->fail;
            }
            if (node->children.find(c) != node->children.end()) { //sprawdza, czy dziecko istnieje, jesli istnieje to przechodzi do dziecka
                node = node->children[c];
            }
            if (node->isEndOfWord && position-2 > lastFindPosition) {
                finded += node->isEndOfWordLetter;
                lastFindPosition = position;
            }
            position++;
        }
    }
};


void swp(std::vector<int> &vec, int index1, int index2) {
        int temp = vec[index1];
        vec[index1] = vec[index2];
        vec[index2] = temp;
}


std::vector<int> crtSffxArr(const std::string &s) {
    int n = s.size();
    std::vector<int> suffixArray(n), rank(n), temp(n);


    for (int i = 0; i < n; ++i) {
        suffixArray[i] = i;
        rank[i] = s[i];
    }

    for (int k = 1; k < n; k *= 2) {
    
        auto compare = [&](int a, int b) {
            if (rank[a] != rank[b]) return rank[a] < rank[b];
            int ra = (a + k < n) ? rank[a + k] : -1;
            int rb = (b + k < n) ? rank[b + k] : -1;
            return ra < rb;
        };

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (!compare(suffixArray[i], suffixArray[j])) {
                    swp(suffixArray, i, j);
                }
            }
        }

        temp[suffixArray[0]] = 0;
        for (int i = 1; i < n; ++i) {
            temp[suffixArray[i]] = temp[suffixArray[i - 1]] + compare(suffixArray[i - 1], suffixArray[i]);
        }
        rank = temp;
    }

    return suffixArray;
}


std::vector<int> crtLCParr(const std::string &s, const std::vector<int> &suffixArray) {
    int n = s.size();
    std::vector<int> rank(n), lcp(n);

    for (int i = 0; i < n; ++i) {
        rank[suffixArray[i]] = i;
    }

    int h = 0;
    for (int i = 0; i < n; ++i) {
        if (rank[i] > 0) {
            int j = suffixArray[rank[i] - 1];
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) {
                h++;
            }
            lcp[rank[i]] = h;
            if (h > 0) h--;
        }
    }

    return lcp;
}

bool contains(const std::vector<std::string>& vec, const std::string& str) {
    for (const auto& item : vec) {
        if (item == str) {
            return true;
        }
    }
    return false; 
}

void pushBackUnique(std::vector<std::string>& vec, const std::string& str) {
    if (!contains(vec, str)) {
        vec.push_back(str);
    }
}


std::string fndLngstRptdSbstr(const std::string &s) {
    if (s.empty()) return "brak";

    std::vector<int> suffixArray = crtSffxArr(s);
    std::vector<int> lcp = crtLCParr(s, suffixArray);
    
    int maxLength = 0;
    std::vector<std::string> longestSubstrings;
    std::string substr;

    for (int i = 1; i < lcp.size(); ++i) {
        if (lcp[i] > maxLength) {
            maxLength = lcp[i];
            longestSubstrings.clear();
            if(maxLength > 1){
            		pushBackUnique( longestSubstrings, s.substr(suffixArray[i], maxLength) );
            	//longestSubstrings.push_back(s.substr(suffixArray[i], maxLength));
            }
        } else if (lcp[i] == maxLength && maxLength > 1) {
            	pushBackUnique( longestSubstrings, s.substr(suffixArray[i], maxLength) );
            //longestSubstrings.push_back(s.substr(suffixArray[i], maxLength));
        }
    }

    if (longestSubstrings.empty()) {
        return {"brak"};
    } else {
    	substr = longestSubstrings[0];
        for(int i=1; i<longestSubstrings.size(); i++){
        	substr = substr + ' ' + longestSubstrings[i];
        }
        
        return substr;
        //return std::vector<std::string>(longestSubstrings.begin(), longestSubstrings.end());
    }
}


int main() {

	int t, amino_max;
	char ch;
	std::string lets, aminos;
	std::vector<std::string> pattern;
	std::vector< std::vector<std::string> > patterns;
	AhoCorasick ac;
	
	
	
	std::cin >> t;
	
	while(t--){
		patterns.clear();
	
		std::cin >> amino_max;
		
		for(int i=0; i<amino_max; i++){
			pattern.clear();
			std::cin >> lets;
			pattern.push_back(lets);
			int j = 6;
			do {
				std::cin >> lets;
				pattern.push_back(lets);
				j--;
			} while( lets.length() == 3 && std::cin.get() != '\n' && j);
			patterns.push_back(pattern);
		}
		std::cin >> lets;
		//std::cout << lets << std::endl;
		/*
		for(int i=0; i<patterns.size(); i++){
			for(int j=0; j<patterns[i].size(); j++){
				std::cout << patterns[i][j] << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << lets << std::endl;
		*/
		
		for (int i=0; i<patterns.size(); i++) {
		
			for (int j=1; j<patterns[i].size(); j++){
				ac.insert(patterns[i][j], patterns[i][0]);
			}
		}
		//std::cout << lets << std::endl;
		ac.buildFailureLinks();
		ac.search(lets, aminos);
		//std::cout << aminos << std::endl;
		std::cout << fndLngstRptdSbstr(aminos) << std::endl;
		
		ac = AhoCorasick();
		aminos = "";
	}
	
    return 0;
}

