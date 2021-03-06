#include "gridpoint.cpp"

class Grid{
  static const int TETRIS_LENGTH = 20;
  static const int TETRIS_WIDTH = 10;
  
  GridPoint m_objPoints;

  public:
    void initialize(int intStartColor)
    {
      for(int i=0; i<TETRIS_WIDTH; i++)
      {
        for (int j=0; j<TETRIS_LENGTH; j++)
        {
          m_objPoints.Points[i][j] = 1;
        }
      }
    }
  
    void highlightOneRow(int intRow, int intStartColor, int intNewColor)
    {
      for (int i=0; i<TETRIS_LENGTH; i++)
      {
        for (int j=0; j<(TETRIS_WIDTH); j++)
        {
          if (i == intRow) m_objPoints.Points[j][i] = intNewColor;
          else m_objPoints.Points[j][i] = intStartColor;
        }
      }
    }

    GridPoint getPoints () const
    {
      return m_objPoints;
    }
};

