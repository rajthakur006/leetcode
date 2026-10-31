class Solution {
public:
    void dfs(vector<vector<int>>& image, int r, int c,
             int oldColor, int newColor) {

        int m = image.size();
        int n = image[0].size();

        // Boundary check + check original color
        if (r < 0 || c < 0 || r >= m || c >= n ||
            image[r][c] != oldColor) {
            return;
        }

        // Change the pixel color
        image[r][c] = newColor;

        // Visit all 4 adjacent directions
        dfs(image, r + 1, c, oldColor, newColor); // Down
        dfs(image, r - 1, c, oldColor, newColor); // Up
        dfs(image, r, c + 1, oldColor, newColor); // Right
        dfs(image, r, c - 1, oldColor, newColor); // Left
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image,
                                  int sr, int sc, int color) {

        int oldColor = image[sr][sc];

        // Important edge case
        if (oldColor == color) {
            return image;
        }

        dfs(image, sr, sc, oldColor, color);

        return image;
    }
};