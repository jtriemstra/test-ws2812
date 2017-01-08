#include "grid.cpp"

class Game {
  private:
        Grid m_objGrid;
        void (*m_fnRefreshDisplay)(GridPoint);
        //GridEnums::Command (*m_fnReceiveInput)();

  public:
        Game(void (*fnRefreshDisplay)(GridPoint)/*, GridEnums::Command(*fnReceiveInput)()*/)
        {
            m_fnRefreshDisplay = fnRefreshDisplay;
            //m_fnReceiveInput = fnReceiveInput;
        }
        
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

        void initialize(int intColor)
        {
          m_objGrid.initialize(intColor);
        }

        void highlightOneRow(int intRow, int intStartColor, int intNewColor)
        {
          m_objGrid.highlightOneRow(intRow, intStartColor, intNewColor);
        }

};

