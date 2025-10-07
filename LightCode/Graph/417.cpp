#include<iostream>
#include<vector>
#include<queue>

#define OCEAN_PACIFIC 1
#define OCEAN_ATLANTIC 2

#define CELL_EXPLORED 1

template<typename T>
using VECTOR = std::vector<T>;

template<typename T>
using MATRIX = std::vector<std::vector<T>>;

template<typename T>
using QUEUE = std::queue<T>;

//
class Terrain{
    public:
        int x, y;

        Terrain(int x, int y){
            this->x = x;
            this->y = y;
        }

        Terrain top(){
            return Terrain(this->x, this->y+1);
        }

        Terrain button(){
            return Terrain(this->x, this->y-1);
        }

        Terrain right(){
            return Terrain(this->x-1, this->y);
        }

        Terrain left(){
            return Terrain(this->x+1, this->y);
        }

        void display(){
            std::printf("( %i, %i )\n", this->x, this->y);
        }

        bool valid(int x_init, int x_end, int y_init, int y_end){
            return this->x >= x_init && this->x <= x_end &&
                    this->y >= y_init && this->y <= y_end;
        }
};

void display_matrix(MATRIX<int> matrix){
    for(size_t i=0; i<matrix.size(); ++i){
        for(size_t j=0; j<matrix[i].size(); ++j)
            std::printf("%i ", matrix[i][j]);
        std::printf("\n");
    }
    std::printf("\n");
}

//
class Solution{
    public:
        MATRIX<int> pacificAtlantic(MATRIX<int> &board){
            size_t board_height = board.size(),
                   board_width = board[0].size();

            MATRIX<int>
                board_filled(board_height, VECTOR<int>(board_width, 0)),
                board_explored(board_height, VECTOR<int>(board_width, 0));

            // Fill board_filled with OCEAN_PACIFIC value
            for(size_t i=0; i<board_width; ++i){
                matrix_bfs_fill(board, board_filled, board_explored, i, 0, OCEAN_PACIFIC);
            }

            for(size_t i=0; i<board_height; ++i){
                matrix_bfs_fill(board, board_filled, board_explored, 0, i, OCEAN_PACIFIC);
            }

            // display_matrix(board_explored);
            // display_matrix(board);

            // Reset board_explored
            for(size_t i=0; i<board_height; ++i){
                for(size_t j=0; j<board_width; ++j){
                    board_explored[i][j] = 0;
                }
            }

            // Fill board_filled width OCEAN_ATLANTIC value
            for(size_t i=0; i<board_width; ++i){
                matrix_bfs_fill(board, board_filled, board_explored, i, board_height-1, OCEAN_ATLANTIC);
            }

            for(size_t i=0; i<board_height; ++i){
                matrix_bfs_fill(board, board_filled, board_explored, board_width-1, i, OCEAN_ATLANTIC);
            }

            // display_matrix(board_explored);
            // display_matrix(board_filled);

            // Search for cell with OCEAN_PACIFIC + OCEAN_ATLANTIC value
            VECTOR<VECTOR<int>> result;
            for(size_t i=0; i<board_height; ++i){
                for(size_t j=0; j<board_width; ++j){
                    if(board_filled[i][j] == OCEAN_PACIFIC + OCEAN_ATLANTIC){
                        // std::printf("%li %li\n", i, j);
                        result.push_back({(int)i, (int)j});
                    }
                }
            }

            return result;
            // return {};
        }
        
    private:
        void matrix_bfs_fill(
                const MATRIX<int> matrix, MATRIX<int> &matrix_fill, MATRIX<int> &matrix_explored,
                size_t x, size_t y, int fill_value
                ){
            if(matrix_explored[y][x])
                return;

            QUEUE<Terrain> queue;
            queue.push(Terrain(x, y));

            matrix_fill[y][x] += fill_value;
            matrix_explored[y][x] = 1;

            while(1){
                QUEUE<Terrain> queue_new;

                while(!queue.empty()){
                    Terrain cell_curr = queue.front();

                    VECTOR<Terrain> cells_adj = { cell_curr.top(), cell_curr.button(), cell_curr.left(), cell_curr.right() };

                    for(size_t i=0; i<cells_adj.size(); ++i){
                        int x = cells_adj[i].x,
                            y = cells_adj[i].y;

                        if(!cells_adj[i].valid(0, matrix[0].size()-1, 0, matrix.size()-1))
                            continue;

                        if(matrix_explored[y][x])
                            continue;

                        if(matrix[y][x] < matrix[cell_curr.y][cell_curr.x])
                            continue;

                        //
                        // cells_adj[i].display();

                        queue_new.push(cells_adj[i]);

                        matrix_fill[y][x] += fill_value;
                        matrix_explored[y][x] = 1;
                    }
                    
                    //
                    queue.pop();
                }

                if(queue_new.empty())
                    break;

                queue = queue_new;
            }
        }

};

// {{1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4}}
// {{1,1}, {1,1}, {1,1}, {1,1}}
