#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif

#include "inc.h"
NS_BEGIN(elloop)
NS_BEGIN(intersection_of_linklist)

class Solution {
public:
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(nullptr) {}
	};
	size_t len(ListNode * head) {
		auto p(head);
		size_t n(0);
		while (p != nullptr) {
			++n;
			p = p->next;
		}
		return n;
	}

	ListNode* findIntersection(ListNode* p, ListNode *q) {
		if (p == nullptr || q == nullptr) {
			return nullptr;
		}

		auto result(p);
		auto p1(p), p2(q);
		while (p1 != nullptr && p2 != nullptr) {
			if (p1->val != p2->val) {
				result = p1->next;
			}
			p1 = p1->next;
			p2 = p2->next;
		}
		return result;
	}

	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {

		// O(n1) + O(n2)
		size_t n1 = len(headA);
		size_t n2 = len(headB);

		auto p(headA), q(headB);
		if (n1 < n2) {
			// O(n2 - n1)
			while (n1 < n2) {
				++n1;
				q = q->next;
			}
		}
		else if (n2 < n1) {
			// O(n1 - n2)
			while (n2 < n1) {
				++n2;
				p = p->next;
			}

		}
		// same length.
		// O(|n1 - n2|)
		return findIntersection(p, q);
	}
};

NS_END(intersection_of_linklist)
NS_END(elloop)