#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
using namespace std;
class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		int size = nums.size();
		vector<int> ret;
		for (int i = 0; i < size - 1; ++i)
		{
			int sum = nums[i];
			int j = i + 1;
			while (sum != target && j < size)
			{
				sum += nums[j];
				j++;
			}

			if (target == sum)
			{
				ret.push_back(i);
				ret.push_back(j - 1);
				break;
			}
		}
		return ret;
	}
};

int testaa(int&& a)
{
	return a + 1;
}

class TestCA
{
public:
	virtual void print()
	{
		cout << "TestCA" << endl;
	}
};

class TestCB : public TestCA
{
public:
	virtual void print()
	{
		cout << "TestCB" << endl;
	}
};

#include "net/tcp_client.h"
#include "net/net_object_mgr.h"
using namespace std;
using namespace game_net;
int main(int argc,char** argv)
{
	std::string addr("127.0.0.1");
	int port = 9998;
	if (argc >= 2)
	{
		addr = argv[0];
		port = atoi(argv[1]);
	}
	//int a, &ra = a, &&ref = ra;
	asio::io_service ios;
	std::shared_ptr<tcp_client> tp = make_shared<tcp_client>(ios, net_object_mgr::instance()->generate_net_object());

	tp->Connect(addr, port);
	
	while (true)
	{
		ios.run();
	}
	
	return 0;
}

class Solution2 {
public:
	double GetMid(vector<int>& vec, int l, int r)
	{
		int sum = l + r;
		if (sum % 2)
		{
			return (vec[sum / 2] + vec[sum / 2 + 1]) / 2.0;
		}

		return vec[sum / 2];
	}
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int l1 = 0, l2 = nums1.size() - 1, r1 = 0, r2 = nums2.size() - 1;

		while (l1 < l2 - 1 && r1 < r2 - 1)
		{
			double m1 = GetMid(nums1, l1, l2);
			double m2 = GetMid(nums2, r1, r2);
			int c1 = (l2 - l1 - 1) / 2;
			int c2 = (r2 - r1 - 1) / 2;
			int cutLength = c1 < c2 ? c1 : c2;
			if (m1 < m2)
			{
				l1 += cutLength;
				r2 -= cutLength;
			}
			else if (m1 > m2)
			{
				l2 -= cutLength;
				r1 += cutLength;
			}
			else
			{
				return m1;
			}
		}

		if (l1 > l2 && r1 > r2)
		{
			return 0;
		}
		else if (l1 > l2)
		{
			return GetMid(nums2, r1, r2);
		}
		else if (r1 > r2)
		{
			return GetMid(nums1, l1, l2);
		}
		int lv1 = nums1[l1];
		int lv2 = nums1[l2];
		int rv1 = nums2[r1];
		int rv2 = nums2[r2];
		int lm1 = (l2 + l1) / 2;
		int lm2 = (l2 + l1 + 1) / 2;
		int rm1 = (r2 + r1) / 2;
		int rm2 = (r2 + r1 + 1) / 2;
		int lmv1 = nums1[lm1];
		int lmv2 = nums1[lm2];
		int rmv1 = nums2[rm1];
		int rmv2 = nums2[rm2];

		if (l1 == l2 && r1 == r2)
		{
			return (lv1 + rv1) / 2.0;
		}
		else if (l1 == l2)
		{
			if (lv1 < rmv1)
			{
				return rmv1;
			}
			else if (lv1 < rmv2)
			{
				return lv1;
			}
			return rmv2;
		}
		else if (r1 == r2)
		{
			if (rv1 < lmv1)
			{
				return lmv1;
			}
			else if (rv1 < lmv2)
			{
				return rv1;
			}
			return lmv2;
		}
		else if (l2 <= r1)
		{

		}
		else if (r2 <= l1)
		{

		}
		else if (l1 >= r1 && l2 <= r2)
		{

		}
		else if (r1 >= l1 && r2 <= l2)
		{

		}
		else if (l2 >= r1)
		{

		}
		else //r2 >= l1
		{

		}
		return 0;
	}
};