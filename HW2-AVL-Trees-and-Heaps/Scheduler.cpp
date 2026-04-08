/**
 * Title: AVL Trees and Heaps
 * Author: Yakup Emre Celebi
 * ID: 22302267
 * Section: 2
 * Homework: 2
 * Description: Task scheduler simulation using Max-Heap and Min-Heap.
 */

#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

struct Task
{
    int id;
    long long arrival_time;
    long long duration;
    long long initial_priority;

    long long base_priority;
};

struct Processor
{
    int id;
    long long available_time;
};

class TaskMaxHeap
{
private:
    Task *heapArray;
    int capacity;
    int currentSize;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return (2 * i) + 1; }
    int rightChild(int i) { return (2 * i) + 2; }

    void siftUp(int index)
    {
        while (index > 0 && heapArray[index].base_priority >= heapArray[(index - 1) / 2].base_priority)
        {

            if (heapArray[index].base_priority == heapArray[(index - 1) / 2].base_priority)
            {
                if (heapArray[index].arrival_time < heapArray[(index - 1) / 2].arrival_time)
                {
                    Task temp = heapArray[index];
                    heapArray[index] = heapArray[(index - 1) / 2];
                    heapArray[(index - 1) / 2] = temp;
                }
                else
                {
                    break;
                }
            }
            else
            {
                Task temp = heapArray[index];
                heapArray[index] = heapArray[(index - 1) / 2];
                heapArray[(index - 1) / 2] = temp;
            }
            index = (index - 1) / 2;
        }
    }

    void siftDown(int index)
    {
        while ((index + 1) * 2 - 1 < currentSize)
        {

            int maxIndex;
            if ((index + 1) * 2 >= currentSize)
            {
                maxIndex = (index + 1) * 2 - 1;
            }
            else
            {
                if (heapArray[(index + 1) * 2].base_priority > heapArray[(index + 1) * 2 - 1].base_priority)
                {
                    maxIndex = (index + 1) * 2;
                }
                else if (heapArray[(index + 1) * 2].base_priority < heapArray[(index + 1) * 2 - 1].base_priority)
                {
                    maxIndex = (index + 1) * 2 - 1;
                }
                else if (heapArray[(index + 1) * 2].base_priority == heapArray[(index + 1) * 2 - 1].base_priority)
                {
                    if (heapArray[(index + 1) * 2].arrival_time < heapArray[(index + 1) * 2 - 1].arrival_time)
                    {
                        maxIndex = (index + 1) * 2;
                    }
                    else
                    {
                        maxIndex = (index + 1) * 2 - 1;
                    }
                }
            }

            if (heapArray[index].base_priority < heapArray[maxIndex].base_priority)
            {
                Task temp = heapArray[index];
                heapArray[index] = heapArray[maxIndex];
                heapArray[maxIndex] = temp;
            }
            else if (heapArray[index].base_priority == heapArray[maxIndex].base_priority)
            {
                if (heapArray[index].arrival_time > heapArray[maxIndex].arrival_time)
                {
                    Task temp = heapArray[index];
                    heapArray[index] = heapArray[maxIndex];
                    heapArray[maxIndex] = temp;
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
            index = maxIndex;
        }
    }

public:
    TaskMaxHeap(int cap)
    {
        capacity = cap;
        currentSize = 0;
        heapArray = new Task[capacity];
    }

    ~TaskMaxHeap()
    {
        delete[] heapArray;
    }

    void insert(Task t)
    {

        if (currentSize != capacity)
        {
            heapArray[currentSize] = t;
            siftUp(currentSize);
            currentSize++;
        }
    }

    Task extractMax()
    {
        Task root = heapArray[0];
        heapArray[0] = heapArray[currentSize - 1];
        currentSize--;
        siftDown(0);
        return root;
    }

    bool isEmpty()
    {
        return currentSize == 0;
    }

    int getSize()
    {
        return currentSize;
    }
};

class ProcessorMinHeap
{
private:
    Processor *heapArray;
    int capacity;
    int currentSize;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return (2 * i) + 1; }
    int rightChild(int i) { return (2 * i) + 2; }

    void siftUp(int index)
    {
        while (index > 0 && heapArray[index].available_time <= heapArray[(index - 1) / 2].available_time)
        {

            if (heapArray[index].available_time == heapArray[(index - 1) / 2].available_time)
            {
                if (heapArray[index].id < heapArray[(index - 1) / 2].id)
                {
                    Processor temp = heapArray[index];
                    heapArray[index] = heapArray[(index - 1) / 2];
                    heapArray[(index - 1) / 2] = temp;
                }
                else
                {
                    break;
                }
            }
            else
            {
                Processor temp = heapArray[index];
                heapArray[index] = heapArray[(index - 1) / 2];
                heapArray[(index - 1) / 2] = temp;
            }
            index = (index - 1) / 2;
        }
    }

    void siftDown(int index)
    {
        while ((index + 1) * 2 - 1 < currentSize)
        {

            int minIndex;
            if ((index + 1) * 2 >= currentSize)
            {
                minIndex = (index + 1) * 2 - 1;
            }
            else
            {
                if (heapArray[(index + 1) * 2].available_time < heapArray[(index + 1) * 2 - 1].available_time)
                {
                    minIndex = (index + 1) * 2;
                }
                else if (heapArray[(index + 1) * 2].available_time > heapArray[(index + 1) * 2 - 1].available_time)
                {
                    minIndex = (index + 1) * 2 - 1;
                }
                else if (heapArray[(index + 1) * 2].available_time == heapArray[(index + 1) * 2 - 1].available_time)
                {
                    if (heapArray[(index + 1) * 2].id < heapArray[(index + 1) * 2 - 1].id)
                    {
                        minIndex = (index + 1) * 2;
                    }
                    else
                    {
                        minIndex = (index + 1) * 2 - 1;
                    }
                }
            }

            if (heapArray[index].available_time > heapArray[minIndex].available_time)
            {
                Processor temp = heapArray[index];
                heapArray[index] = heapArray[minIndex];
                heapArray[minIndex] = temp;
            }
            else if (heapArray[index].available_time == heapArray[minIndex].available_time)
            {
                if (heapArray[index].id > heapArray[minIndex].id)
                {
                    Processor temp = heapArray[index];
                    heapArray[index] = heapArray[minIndex];
                    heapArray[minIndex] = temp;
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
            index = minIndex;
        }
    }

public:
    ProcessorMinHeap(int cap)
    {
        capacity = cap;
        currentSize = 0;
        heapArray = new Processor[capacity];
    }

    ~ProcessorMinHeap()
    {
        delete[] heapArray;
    }

    void insert(Processor p)
    {
        if (currentSize != capacity)
        {
            heapArray[currentSize] = p;
            siftUp(currentSize);
            currentSize++;
        }
    }

    Processor extractMin()
    {

        Processor root = heapArray[0];
        heapArray[0] = heapArray[currentSize - 1];
        currentSize--;
        siftDown(0);
        return root;
    }

    Processor getMin()
    {
        return heapArray[0];
    }

    bool isEmpty()
    {
        return currentSize == 0;
    }
};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Usage: ./scheduler <input_file>" << endl;
        return 1;
    }

    auto start_time_metric = chrono::high_resolution_clock::now();

    ifstream inputFile(argv[1]);
    if (!inputFile)
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    int N, M;
    inputFile >> N >> M;

    Task *allTasks = new Task[N];

    for (int i = 0; i < N; i++)
    {
        long long temp_arr, temp_dur, temp_prio;

        inputFile >> temp_arr >> temp_dur >> temp_prio;

        allTasks[i].id = i;
        allTasks[i].arrival_time = temp_arr;
        allTasks[i].duration = temp_dur;
        allTasks[i].initial_priority = temp_prio;
        allTasks[i].base_priority = temp_prio - temp_arr;
    }
    inputFile.close();

    TaskMaxHeap waitQueue(N);
    ProcessorMinHeap processors(M);

    for (int i = 0; i < M; i++)
    {
        Processor p;
        p.id = i;
        p.available_time = 0;
        processors.insert(p);
    }

    long long T = 0;
    int taskIndex = 0;
    int completedTasks = 0;

    while (completedTasks < N)
    {
        while (taskIndex < N && allTasks[taskIndex].arrival_time <= T)
        {
            waitQueue.insert(allTasks[taskIndex]);
            taskIndex++;
        }

        if (!waitQueue.isEmpty() && processors.getMin().available_time <= T)
        {
            Task bestTask = waitQueue.extractMax();
            Processor bestProc = processors.extractMin();

            long long startTime = T;
            long long finishTime = startTime + bestTask.duration;

            cout << "Process " << bestTask.id << ": Start=" << startTime << ", Finish=" << finishTime << "\n";

            bestProc.available_time = finishTime;
            processors.insert(bestProc);

            completedTasks++;
        }
        else
        {

            if (waitQueue.isEmpty())
            {
                T = allTasks[taskIndex].arrival_time;
            }
            else
            {
                T = processors.getMin().available_time;
            }
        }
    }

    auto end_time_metric = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> duration_metric = end_time_metric - start_time_metric;

    cout << "Total program execution time: " << duration_metric.count() << " ms\n";

    delete[] allTasks;

    return 0;
}