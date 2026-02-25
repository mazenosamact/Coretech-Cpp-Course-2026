#include <iostream>
#include <queue>
#include <vector>
// c++20: std::span

using namespace std;

class MovingAverage
{
    queue<int> m_window;
    int m_windows_size;
    double m_average;
    double m_running_sum = 0.0;
    bool m_isReady = false;
public:
    MovingAverage(int s):m_windows_size(s){}

    void addReading(int r)
    {
        if(m_windows_size == m_window.size())
        {
            m_isReady = true;
            m_running_sum -= m_window.front();
            m_window.pop();
            m_running_sum += r;
            m_window.push(r);
            m_average = m_running_sum / m_windows_size ;
        }
        else if (m_windows_size > m_window.size())
        {
            m_window.push(r);
            m_running_sum += r ;
        }
    }
    bool isReady() { return m_isReady; }
    double getAverage() { return m_average; }
};


int test_queue_main(int argc, char* argv[])
{
    std::vector<int> readings = {1,1,1,1,1,1,1};
    std::vector<double> avgs; avgs.reserve(readings.size());

    MovingAverage mv(3);

    for(auto i: readings)
    {
        mv.addReading(i);

        if(mv.isReady())
        {
            avgs.push_back(mv.getAverage());
        }
    }

}