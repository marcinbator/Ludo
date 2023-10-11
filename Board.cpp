#include "Board.h"

Board::Board(Tile* tiles, RenderWindow* window)
{
    this->centerX = window->getSize().x / 2;
    this->centerY = window->getSize().y / 2;
    this->tiles = tiles;
    drawBoard(window);
    setIds();
}

void Board::drawBoard(RenderWindow* window)
{
    int id = 0;
    //bottom
    for (int i = 1; i < 5; i++) {
        for (int j = -1; j <= 1; j += 2) {
            tiles[id].drawTile("images/tile.png", centerX + j * tiles[id].getWidth(), centerY + tiles[id].getHeight() * i, window, id);
        }
        tiles[id].drawTile("images/tileRed.png", centerX, centerY + tiles[id].getHeight() * i, window, id);
    }
    for (int i = -1; i <= 1; i++) {
        tiles[id].drawTile("images/tile.png", centerX + i * tiles[id].getWidth(), centerY + tiles[id].getHeight() * 5, window, id);
    }
    //top
    for (int i = 1; i <= 4; i++) {
        for (int j = -1; j <= 1; j += 2) {
            tiles[id].drawTile("images/tile.png", centerX + j * tiles[id].getWidth(), centerY - tiles[id].getHeight() * i, window, id);
        }
        tiles[id].drawTile("images/tileGreen.png", centerX, centerY - tiles[id].getHeight() * i, window, id);
    }
    for (int i = -1; i <= 1; i++) {
        tiles[id].drawTile("images/tile.png", centerX + i * tiles[id].getWidth(), centerY - tiles[id].getHeight() * 5, window, id);
    }
    //left
    tiles[id].drawTile("images/tileBlue.png", centerX - tiles[id].getWidth(), centerY, window, id);
    for (int i = 2; i <= 4; i++) {
        for (int j = -1; j <= 1; j += 2) {
            tiles[id].drawTile("images/tile.png", centerX - tiles[id].getWidth() * i, centerY + j * tiles[id].getHeight(), window, id);
        }
        tiles[id].drawTile("images/tileBlue.png", centerX - tiles[id].getWidth() * i, centerY, window, id);
    }
    for (int i = -1; i <= 1; i++) {
        tiles[id].drawTile("images/tile.png", centerX - tiles[id].getWidth() * 5, centerY - i * tiles[id].getHeight(), window, id);
    }
    //right
    tiles[id].drawTile("images/tileYellow.png", centerX + tiles[id].getWidth(), centerY, window, id);
    for (int i = 2; i <= 4; i++) {
        for (int j = -1; j <= 1; j += 2) {
            tiles[id].drawTile("images/tile.png", centerX + tiles[id].getWidth() * i, centerY + j * tiles[id].getHeight(), window, id);
        }
        tiles[id].drawTile("images/tileYellow.png", centerX + tiles[id].getWidth() * i, centerY, window, id);
    }
    for (int i = -1; i <= 1; i++) {
        tiles[id].drawTile("images/tile.png", centerX + tiles[id].getWidth() * 5, centerY - i * tiles[id].getHeight(), window, id);
    }
    //arrows
    tiles[12].drawTile("images/Rarrow.png", tiles[12].getPositionX(), tiles[12].getPositionY(), window);
    tiles[42].drawTile("images/Barrow.png", 90, tiles[42].getPositionX(), tiles[42].getPositionY(), window);
    tiles[29].drawTile("images/Garrow.png", 180, tiles[29].getPositionX(), tiles[29].getPositionY(), window);
    tiles[53].drawTile("images/Yarrow.png", 270, tiles[53].getPositionX(), tiles[53].getPositionY(), window);
    //bases
    //lefttop
    tiles[id].drawTile("images/tileBlue.png", centerX - tiles[id].getWidth() * 5, centerY - tiles[id].getHeight() * 5, window, id);
    tiles[id].drawTile("images/tileBlue.png", centerX - tiles[id].getWidth() * 4, centerY - tiles[id].getHeight() * 5, window, id);
    tiles[id].drawTile("images/tileBlue.png", centerX - tiles[id].getWidth() * 4, centerY - tiles[id].getHeight() * 4, window, id);
    tiles[id].drawTile("images/tileBlue.png", centerX - tiles[id].getWidth() * 5, centerY - tiles[id].getHeight() * 4, window, id);
    //righttop
    tiles[id].drawTile("images/tileGreen.png", centerX + tiles[id].getWidth() * 5, centerY - tiles[id].getHeight() * 5, window, id);
    tiles[id].drawTile("images/tileGreen.png", centerX + tiles[id].getWidth() * 4, centerY - tiles[id].getHeight() * 5, window, id);
    tiles[id].drawTile("images/tileGreen.png", centerX + tiles[id].getWidth() * 4, centerY - tiles[id].getHeight() * 4, window, id);
    tiles[id].drawTile("images/tileGreen.png", centerX + tiles[id].getWidth() * 5, centerY - tiles[id].getHeight() * 4, window, id);
    //rightbottom
    tiles[id].drawTile("images/tileYellow.png", centerX + tiles[id].getWidth() * 5, centerY + tiles[id].getHeight() * 5, window, id);
    tiles[id].drawTile("images/tileYellow.png", centerX + tiles[id].getWidth() * 4, centerY + tiles[id].getHeight() * 5, window, id);
    tiles[id].drawTile("images/tileYellow.png", centerX + tiles[id].getWidth() * 4, centerY + tiles[id].getHeight() * 4, window, id);
    tiles[id].drawTile("images/tileYellow.png", centerX + tiles[id].getWidth() * 5, centerY + tiles[id].getHeight() * 4, window, id);
    //leftbottom
    tiles[id].drawTile("images/tileRed.png", centerX - tiles[id].getWidth() * 5, centerY + tiles[id].getHeight() * 5, window, id);
    tiles[id].drawTile("images/tileRed.png", centerX - tiles[id].getWidth() * 4, centerY + tiles[id].getHeight() * 5, window, id);
    tiles[id].drawTile("images/tileRed.png", centerX - tiles[id].getWidth() * 4, centerY + tiles[id].getHeight() * 4, window, id);
    tiles[id].drawTile("images/tileRed.png", centerX - tiles[id].getWidth() * 5, centerY + tiles[id].getHeight() * 4, window, id);
}

void Board::setIds() {
    //main route
    tiles[12].setId(1);
    tiles[9].setId(2);
    tiles[6].setId(3);
    tiles[3].setId(4);
    tiles[0].setId(5);
    tiles[32].setId(6);
    tiles[35].setId(7);
    tiles[38].setId(8);
    tiles[40].setId(9);
    tiles[41].setId(10);
    tiles[42].setId(11);
    tiles[37].setId(12);
    tiles[34].setId(13);
    tiles[31].setId(14);
    tiles[15].setId(15);
    tiles[18].setId(16);
    tiles[21].setId(17);
    tiles[24].setId(18);
    tiles[27].setId(19);
    tiles[28].setId(20);
    tiles[29].setId(21);
    tiles[25].setId(22);
    tiles[22].setId(23);
    tiles[19].setId(24);
    tiles[16].setId(25);
    tiles[44].setId(26);
    tiles[47].setId(27);
    tiles[50].setId(28);
    tiles[55].setId(29);
    tiles[54].setId(30);
    tiles[53].setId(31);
    tiles[51].setId(32);
    tiles[48].setId(33);
    tiles[45].setId(34);
    tiles[1].setId(35);
    tiles[4].setId(36);
    tiles[7].setId(37);
    tiles[10].setId(38);
    tiles[14].setId(39);
    tiles[13].setId(40);
    //targets
    tiles[11].setId(51);
    tiles[8].setId(52);
    tiles[5].setId(53);
    tiles[2].setId(54);
    tiles[39].setId(61);
    tiles[36].setId(62);
    tiles[33].setId(63);
    tiles[30].setId(64);
    tiles[26].setId(71);
    tiles[23].setId(72);
    tiles[20].setId(73);
    tiles[17].setId(74);
    tiles[52].setId(81);
    tiles[49].setId(82);
    tiles[46].setId(83);
    tiles[43].setId(84);
    //bases
    tiles[70].setId(101);
    tiles[71].setId(102);
    tiles[68].setId(103);
    tiles[69].setId(104);
    tiles[56].setId(111);
    tiles[57].setId(112);
    tiles[59].setId(113);
    tiles[58].setId(114);
    tiles[61].setId(121);
    tiles[60].setId(122);
    tiles[62].setId(123);
    tiles[63].setId(124);
    tiles[66].setId(131);
    tiles[67].setId(132);
    tiles[65].setId(133);
    tiles[64].setId(134);
}