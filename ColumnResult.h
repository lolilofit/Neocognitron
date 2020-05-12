//
// Created by User on 29.04.2020.
//

#ifndef NEOCOGNITRON_COLUMNRESULT_H
#define NEOCOGNITRON_COLUMNRESULT_H


#include <vector>

class Position {
public:
    int plane;
    int x;
    int y;
    float val;

    Position(int plane, int x, int y, float val) {
        this->plane = plane;
        this->x = x;
        this->y = y;
        this->val = val;
    }
};


class ColumnResult {
private:
    int plane_size;
    int plane_number;

    std::vector<std::vector<std::vector<float>>> data;

    Position* find_max(std::vector<std::vector<std::vector<float>>> &data_part, int w_size, int center_shift_x, int center_shift_y);
public:
    ColumnResult(int plane_size, int planes_number);
    void get_planes_parts(int x, int y, int w_size, std::vector<std::vector<float>> &res);
    std::vector<float> get_plane_part(int plane_number, int x, int y, int w_size);
    void add_result(int plane_number, int x, int y, float res);
    std::vector<Position*> get_cell_to_update(int w_size);
    std::vector<std::vector<std::vector<float>>> get_plane_part_twodim(int x, int y, int w_size);

    std::vector<std::vector<float>> get_part_plane_twodim(int plane, int x, int y, int w_size);
    std::vector<float> get_part_plane(int plane, int x, int y, int w_size);

    void set_plane(int plane_number, std::vector<std::vector<float>> &pl);

    int get_planes_number();

    int add_new_plane();

    void calkData();

    void summ_data();

    int get_plane_size();

    float get_val(int plane_num);
};


#endif //NEOCOGNITRON_COLUMNRESULT_H
