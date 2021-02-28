//
// Created by User on 29.04.2020.
//

#include <map>
#include <iostream>
#include <cmath>
#include "ColumnResult.h"


std::vector<float> ColumnResult::get_part_plane(int plane, int x, int y, int w_size) {
    std::vector<float> res;
    res.resize(w_size*w_size);

    if(w_size >= plane_size) {
        for(int i = 0; i < w_size; i++) {
            for(int j = 0; j < w_size; j++) {
                if(i >= 0 && i < plane_size && j >= 0 && j < plane_size)
                    res[i*w_size + j] = data[plane][i][j];
                else
                    res[i*w_size + j] = 0.0;
            }
        }
    }
    else {
        int cnt = 0;
        int center_shift = (w_size - 1)/2;
        for(int i = x - center_shift; i <= (x + center_shift); i++) {
            for(int j = y - center_shift; j <= (y + center_shift); j++) {
                //catch exception
                if(i >= 0 && i < plane_size && j >= 0 && j < plane_size)
                    res[cnt] = data[plane][i][j];
                else {
                    res[cnt] = 0.0;
                }
                cnt++;
            }
        }
    }

    return res;
}

void ColumnResult::get_planes_parts(int x, int y, int w_size, std::vector<std::vector<float>> &res) {
    res.resize(plane_number);

    for(int plane = 0; plane < plane_number; plane++) {
        res[plane] = get_part_plane(plane, x, y, w_size);
    }
}

void ColumnResult::add_result(int plane_number, int x, int y, float res) {
    data[plane_number][x][y] = res;
}

std::pair<int, int> move_pos(int point_x, int point_y, int l_center_x, int l_centre_y, int g_center_x, int g_center_y) {
    return std::pair<int, int>(g_center_x - l_center_x + point_x, g_center_y - l_centre_y + point_y);
}

//размерности???
Position* ColumnResult::find_max(std::vector<std::vector<std::vector<float>>> &data_part, int w_size, int center_shift_x, int center_shift_y) {
    if(!data_part.empty()) {
        int x_size = data_part[0].size();
        int y_size = data_part[0][0].size();
        int max_plane_pos = -1;
        int max_x_pos = -1;
        int max_y_pos = -1;
        float max_val = -1.0;

        for (int plane = 0; plane < plane_number; plane++) {
            for (int i = 0; i < x_size; i++) {
                for (int j = 0; j < y_size; j++) {
                    if (data_part[plane][i][j] > max_val) {
                        max_val = data_part[plane][i][j];
                        max_plane_pos = plane;
                        max_x_pos = i;
                        max_y_pos = j;
                    }
                }
            }
        }

        if (max_val > 0.0) {
            int local_center = (w_size - w_size % 2) / 2;
            std::pair<int, int> moved_pos = move_pos(max_x_pos, max_y_pos, local_center, local_center, center_shift_x,
                                                     center_shift_y);
            Position *position = new Position(max_plane_pos, moved_pos.first, moved_pos.second, max_val);
            return position;
        } else {
            return nullptr;
        }
    }
    return nullptr;
}



std::vector<Position*> ColumnResult::get_cell_to_update(int w_size) {
    std::vector<Position*> res;

    int center_shift = (w_size - 1)/2;

    if(w_size == plane_size) {
         Position* position = find_max(data, w_size, center_shift, center_shift);
         res.push_back(position);
    } else {
        for(int i = center_shift; i < (plane_size - center_shift); i++) {
            for(int j = center_shift; j < (plane_size - center_shift); j++) {
                std::vector<std::vector<std::vector<float>>> plane_part = get_plane_part_twodim(i, j, w_size);
                Position* position = find_max(plane_part, w_size, i, j);
                if(position != nullptr) {
                    bool flag = false;
                    for(int k = 0 ; k < res.size(); k++) {
                        if (res[k]->x == position->x && res[k]->y == position->y && res[k]->plane == position->plane) {
                            flag = true;
                        }
                    }
                    if(flag == false)
                        res.push_back(position);
                }
            }
        }
    }

    std::vector<Position*> res_per_plane;
    res_per_plane.resize(plane_number);

    Position* pos;

    for(int plane = 0; plane < plane_number; plane++) {
        Position* max_position = nullptr;
        float max_val = 0.0;

        for(int i = 0; i < res.size(); i++) {
            pos = res[i];
            if(pos != nullptr) {
                if (pos->plane == plane) {
                    if (pos->val > max_val) {
                        max_position = pos;
                        max_val = pos->val;
                    }
                }
            }
        }

        res_per_plane[plane] = max_position;
    }

    return res_per_plane;
}


std::vector<std::vector<float>> ColumnResult::get_part_plane_twodim(int plane, int x, int y, int w_size) {
    std::vector<std::vector<float>> res;

    res.resize(w_size);
    for(int j = 0; j < w_size; j++) {
        res[j].resize(w_size);
    }

    if(w_size == plane_size) {
        for(int i = 0; i < w_size; i++) {
            for(int j = 0; j < w_size; j++) {
                res[i][j] = data[plane][i][j];
            }
        }
    } else {
        int center_shift = (w_size - 1)/2;
        for(int i = x - center_shift; i <= (x + center_shift); i++) {
            for (int j = y - center_shift; j <= (y + center_shift); j++) {
                //catch exception
                if(i >= 0 && i < plane_size && j >= 0 && j < plane_size)
                    res[i - x + center_shift][j - y + center_shift] = data[plane][i][j];
                else
                    res[i - x + center_shift][j - y + center_shift] = 0.0;
            }
        }
    }
    return res;
}

std::vector<std::vector<std::vector<float>>> ColumnResult::get_plane_part_twodim(int x, int y, int w_size) {
    std::vector<std::vector<std::vector<float>>> res;
    res.resize(plane_number);

    for(int plane = 0; plane < plane_number; plane++) {
        res[plane] = get_part_plane_twodim(plane, x, y, w_size);
    }

    return res;
}

std::vector<float> ColumnResult::get_plane_part(int plane_number, int x, int y, int w_size) {
    std::vector<float> res;
    res.resize(w_size*w_size);

    if(w_size == plane_size) {
        int cnt = 0;
        for(int i = 0; i < w_size; i++) {
            for(int j = 0; j < w_size; j++) {
                if(i >= 0 && i < plane_size && j >= 0 && j < plane_size)
                    res[cnt] = data[plane_number][i][j];
                else
                    res[cnt] = 0.0f;
                cnt++;
            }
        }
    }
    else {
        int cnt = 0;
        int middle = (w_size - 1)/2;
        for(int i = x - middle; i <= x + middle; i++) {
            for(int j = y - middle; j <= y+middle; j++) {
                //res[i * w_size + j] = data[plane_number][i][j];
                if(i >= 0 && i < plane_size && j >= 0 && j < plane_size)
                    res[cnt] = data[plane_number][i][j];
                else
                    res[cnt] = 0.0;
                cnt++;
            }
        }
    }
    return res;
}

ColumnResult::ColumnResult(int plane_size, int planes_number) {
    this->plane_size = plane_size;
    this->plane_number = planes_number;

    data.resize(planes_number);

    for(int i = 0; i < planes_number; i++) {
        data[i].resize(plane_size);
        for(int j = 0; j < plane_size; j++) {
            data[i][j].resize(plane_size);
        }
    }
}

void ColumnResult::set_plane(int plane_number, std::vector<std::vector<float>> &pl) {
    data[plane_number] = pl;
}

void ColumnResult::calkData() {
    for(int i = 0; i < data.size(); i++) {
        std::vector<std::vector<float>> i_data = data[i];
        for(int j = 0; j < i_data.size(); j++) {
            std::vector<float> ij_data = i_data[j];
            for(int k = 0; k < ij_data.size(); k++) {
                if(ij_data[k] > 0.0f)
                    std::cout<<1;
                else
                    std::cout << ij_data[k];
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }
}

int ColumnResult::get_planes_number() {
    return data.size();
}

int ColumnResult::add_new_plane() {
    plane_number++;

    data.resize(plane_number);

    data[plane_number - 1].resize(plane_size);
    for(int i = 0; i < plane_size; i++) {
        data[plane_number - 1][i].resize(plane_size);
    }

    return plane_number - 1;
}

int ColumnResult::get_plane_size() {
    if(data.empty())
        return 0;
    return data[0][0].size();
}

void ColumnResult::summ_data() {
    std::vector<float> summ;
    summ.resize(data[0].size()*data[0].size());
    for(int i = 0; i < data[0].size()*data[0].size(); i++)
        summ[i] = 0.0;

    for(int i = 0; i < data.size(); i++) {
        std::vector<std::vector<float>> i_data = data[i];

        for(int j = 0; j < i_data.size(); j++) {
            std::vector<float> ij_data = i_data[j];
            for(int k = 0; k < ij_data.size(); k++) {

                summ[j * ij_data.size() + k] += ij_data[k];
            }
        }
    }

    for(int i = 0; i < data[0].size(); i++) {
        for(int j = 0; j < data[0].size(); j++)
            if(summ[i*data[0].size() + j] > 0.0)
                std::cout << 1.0;
            else
                std::cout << 0.0;
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

float ColumnResult::get_val(int plane_num) {
    return data[plane_num][0][0];
}

std::vector<std::vector<std::vector<float>>> ColumnResult::get_data() {
    return data;
}
