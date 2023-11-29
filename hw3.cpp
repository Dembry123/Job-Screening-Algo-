#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void split(int &start1, int &end1, int &start2, int &end2)
{
   if (start1 == end2 - 1)
   {
      end1 = start1;
      start2 = end2;
      return;
   }
   if ((end2 - start1) % 2 == 0)
   {
      int middle;
      middle = (end2 - start1) / 2;
      end1 = start1 + middle;
      start2 = end1 + 1;
      return;
   }
   // start1 == 0 // end2 == 3
   end1 = ((end2 - start1) / 2) + start1; // end1 = 1
   start2 = end1 + 1;
   return;
}

vector<int> combineBestApplicants(const vector<pair<float, float>> &applicants, vector<int> list1, vector<int> list2)
{
   vector<int> sol;

   for (auto i : list1)
   {
      bool eligible = true;
      for (auto j : list2)
      {
         if ((applicants[i].first < applicants[j].first) && (applicants[i].second > applicants[j].second))
         {
             eligible = false;
            break;
         }
      }
      if (eligible)
         sol.push_back(i);
   }

    for (auto i : list2)
    {
        bool eligible = true;
        for (auto j : sol)
        {
            if ((applicants[i].first < applicants[j].first) && (applicants[i].second > applicants[j].second))
            {
                eligible = false;
                break;
            }
        }
        if (eligible)
            sol.push_back(i);
    }

   return sol;
}

vector<int> RecursiveBestApplicants(const vector<pair<float, float>> &applicants, int startIndex, int endIndex)
{
   if (startIndex == endIndex)
   {
      vector<int> temp;
      temp.push_back(startIndex);
      return temp;
   }
   int start1 = startIndex;
   int end1;
   int start2;
   int end2 = endIndex;
   split(start1, end1, start2, end2);

   vector<int> recursive1 = RecursiveBestApplicants(applicants, start1, end1);
   vector<int> recursive2 = RecursiveBestApplicants(applicants, start2, end2);

   return combineBestApplicants(applicants, recursive1, recursive2);
}
vector<int> BestApplicants(const vector<pair<float, float>> &applicants)
{
   return RecursiveBestApplicants(applicants, 0, applicants.size() - 1);
}
