#include <vector>
#include <priority_queue>

using namespace std;

vector<int> smallestRange(vector<vector<int>> &nums)
{
    if (nums.empty())
        return {};
    if (nums.size() == 1)
        return {nums[0][0], nums[0][0]};
    int n = nums.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> iter(nums.size(), 0);
    int maxN = INT_MIN;
    for (int i = 0; i < n; ++i)
    {
        if (nums[i].empty())
            return {};
        maxN = max(maxN, nums[i][0]);
        pq.push({nums[i][0], i});
    }
    //vector<int> res({pq.top().first, maxN});
    //int lastPop = pq.top().second;
    int res1 = pq.top().first, res2 = maxN;
    while (true)
    {
        auto cur = pq.top();
        pq.pop();
        lastPop = cur.second;
        iter[lastPos]++;
        if (iter[lastPos] >= nums[lastPos].size())
            break;
        pq.push({nums[iter[lastPos]], lastPos});
        maxN = max(maxN, nums[iter[lastPos]]);
        if (res2 - res1 > maxN - pq.top().first)
        {
            res1 = pq.top().first;
            res2 = maxN;
        }
    }
    return {res1, res2};
}

int consecutiveNumbersSum(int N)
{
    if(N<2) return 1;
    int res=0, size=1;
    for(int m=1;;m++)
    {
        int mx = N-m*(m-1)/2;
        if(mx<=0)break;
        if(mx%m==0) res++;
    }
    return res;
}

bool lottery(vector<vector<int>>& lot, vector<int>& lucky)
{
	int n = lot.size(), m = lucky.size();
	if(m<n) return false;

}

API:
bool hasNext(stream& int_stream);
pair<int, bool> getNext(stream& int_stream);

vector<int> Sampling(stream& int_stream, int n)
{
	vector<int> res(n, 0);
	int badIndex=-1, goodIndex=n, totalBadCnt=0;
	while(hasNext(int_stream) && goodIndex>0)
	{
		auto nextInt = getNext(int_stream);
		if(nextInt.second)
		{
			goodIndex--；
			if(goodIndex==badIndex)
			{
				int dropIndex = rand()%(badIndex+1);
				swap(res[badIndex], res[dropIndex]);
				badIndex--;
			}
			res[goodIndex] = nextInt.first;
		}
		else
		{
			totalBadCnt++;
			if(badIndex+1==goodIndex)
			{
				int dropIndex = rand()%(totalBadCnt);
				if(dropIndex<=badIndex)
				{
					res[dropIndex] = nextInt.first;
				}
			}
			else
				res[++badIndex] = nextInt.first;
		}
	}
	return res;
}

    class UnionFind
    {
    public: 
        UnionFind()
        {   
        }
        
        pair<string, double> Find(string& str)
        {
            if(parents[x].first != x)
            {
                parents[x]=Find(parents[x]);
                value[x] = value[x]*value[parents[x]];
            }
            return parents[x];
        }

        double getValue(string& x)
        {
            if(!dict.count(x)) return -1.0;
            return value[dict[x]];
        }
        
        bool Union(string& x, string& y, double v)
        {
            if(!dict.count(x))
            {
                cnt++;
                dict[x] = cnt-1;
            }
            if(!dict.count(y))
            {
                cnt++;
                dict[y] = cnt-1;
            }
            int parentX=Find(x);
            int parentY=Find(y);
            if(parentX != parentY)
            {
                parents[parentX] = parentY;
                value[parentX]*=v;
            }
        }
    private:
        unordered_map<string, pair<string, double>> parents;
    };


    class UnionFind
    {
    public: 
        UnionFind()
        {   
        }
        
        pair<string, double> Find(string& str)
        {
            if(parents[x].first != x)
            {
                parents[x]=Find(parents[x]);
                value[x] = value[x]*value[parents[x]];
            }
            return parents[x];
        }

        double getValue(string& x)
        {
            if(!dict.count(x)) return -1.0;
            return value[dict[x]];
        }
        
        bool Union(string& x, string& y, double v)
        {
            if(!dict.count(x))
            {
                cnt++;
                dict[x] = cnt-1;
            }
            if(!dict.count(y))
            {
                cnt++;
                dict[y] = cnt-1;
            }
            int parentX=Find(x);
            int parentY=Find(y);
            if(parentX != parentY)
            {
                parents[parentX] = parentY;
                value[parentX]*=v;
            }
        }
    private:
        unordered_map<string, pair<string, double>> parents;
    };
    
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        if(queries.empty()) return {};
        UnionFind uf(equations.size()*2);
        for(int i=0; i<equations.size(); ++i)
        {
            string a=equations[i].first, b=equations[i].second;
            uf.uion(a, b, values[i]);
        }
        
        vector<double> res(queries.size(), -1.0);
        for(int i=0; i<queries.size(); ++i)
        {
            auto parentA = uf.find(queries[i].first);
            auto parentB = uf.find(queries[i].second);
            if(parentA == parentB && parentA !=-1)
            {
                res[i] = getValue(queries[i].first)/getValue(queries[i].second);
            }
        }
        return res;
    }
