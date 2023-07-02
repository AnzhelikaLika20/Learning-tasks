#include "scorer.h"

int Comp(const Event* event1, const Event* event2) {
    return event1->time < event2->time;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    ScoreTable table;
    std::vector<const Event*> events_copy;
    for (size_t i = 0; i < events.size(); ++i) {
        events_copy.push_back(&(events[i]));
    }
    sort(events_copy.begin(), events_copy.end(), Comp);
    std::map<StudentName, std::map<TaskName, std::pair<int, int>>> tasks;
    for (size_t i = 0; i < events.size(); ++i) {
        if (events_copy[i]->time > score_time) {
            break;
        }
        if (events_copy[i]->event_type == EventType::CheckSuccess) {
            tasks[events_copy[i]->student_name][events_copy[i]->task_name].first = 1;
        } else if (events_copy[i]->event_type == EventType::CheckFailed) {
            tasks[events_copy[i]->student_name][events_copy[i]->task_name].first = 0;
        } else if (events_copy[i]->event_type == EventType::MergeRequestOpen) {
            tasks[events_copy[i]->student_name][events_copy[i]->task_name].second = 1;
        } else {
            tasks[events_copy[i]->student_name][events_copy[i]->task_name].second = 0;
        }
    }
    for (const auto& student : tasks) {
        for (const auto& task : student.second) {
            if (task.second.second == 0 && task.second.first == 1) {
                table[student.first].emplace(task.first);
            }
        }
    }
    return table;
}