#include "grid.cpp"

class Game {
  Grid m_objGrid;

  public:
        GridPoint CurrentDisplay() const
        {
          GridPoint objReturn = m_objGrid.StaticPoints();
          /*if (m_objCurrentShape != NULL)
          {
            for (Point &p : m_objCurrentShape->Points().Points)
            {
                objReturn.Points[p.X][p.Y] = m_objCurrentShape->Type();
            }
          }*/
          return objReturn;
        }

        int CurrentDisplay(int intColumn, int intRow)
        {
          return m_objGrid.StaticPoint(intColumn, intRow);
        }

        void initialize(int intColor)
        {
          m_objGrid.initialize(intColor);
        }

        void highlightOneRow(int intRow, int intStartColor, int intNewColor)
        {
          m_objGrid.highlightOneRow(intRow, intStartColor, intNewColor);
        }

};

