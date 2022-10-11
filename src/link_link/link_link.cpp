#include "link_link/link_link.h"
#include "link_link/block/blank.h"
#include "link_link/block/diamond.h"
#include "link_link/block/path.h"
#include "link_link/block/player.h"
#include "link_link/block/special.h"
#include "link_link/block/wall.h"

#include <iostream>
#include <memory>
#include <random>
#include <set>
#include <spdlog/spdlog.h>
#include <utility>
using namespace link_link::block;
using namespace link_link;
using namespace std;
using namespace spdlog;
using namespace Qt;

link_link::LinkLink::LinkLink()
    : map(generateBlocks(
        {
          mapSize[0],
          mapSize[1],
        },
        GameType::Single)),
      players({
        make_shared<Player>(Point{1, 1}, PlayerType::Player1, Point{0, 0}),
      }),
      linkedPath(), gameTime(0), gameEndStamp(100), hintTimeStamp(0),
      paused(false), flashing(false), gameType(GameType::Single), changed(true)
{}

Map link_link::LinkLink::generateBlocks(Point size, GameType gameType)
{
    Map map;
    for (auto j = 0; j < size.first; ++j) {
        map.push_back({});
        for (auto i = 0; i < size.second; ++i) {
            map[j].push_back(std::make_shared<Blank>());
        }
    }
    for (auto j = 0; j < size.first; ++j) {
        for (auto i = 0; i < size.second; ++i) {
            if (j == 0 || j == size.first - 1 || i == 0 ||
                i == size.second - 1) {
                map[j][i] = std::make_shared<Wall>();
                map[j][i] = std::make_shared<Wall>();
            }
        }
    }
    vector<BlockPointer> weight;
    uint64_t diamonds = (static_cast<uint64_t>(size.first) - 4) *
                        (static_cast<unsigned long long>(size.second) - 4);

    weight.reserve(diamonds);
    for (auto i = 0; i < 2; ++i) {
        weight.push_back(std::make_shared<Special>(SpecialType::PlusOneSecond));
        weight.push_back(std::make_shared<Special>(SpecialType::Shuffle));
        weight.push_back(std::make_shared<Special>(SpecialType::Hint));
        switch (gameType) {
            case link_link::LinkLink::GameType::Single:
                weight.push_back(std::make_shared<Special>(SpecialType::Flash));
                break;
            case link_link::LinkLink::GameType::Contest:
                weight.push_back(
                  std::make_shared<Special>(SpecialType::Freeze));
                weight.push_back(std::make_shared<Special>(SpecialType::Dizzy));
                break;
            default:
                break;
        }
    }

    for (auto i = diamonds - weight.size(); i > 0; -- --i) {
        weight.push_back(std::make_shared<Diamond>(
          static_cast<Color>(i % colors), static_cast<Shape>(i % shapes)));
        weight.push_back(std::make_shared<Diamond>(
          static_cast<Color>(i % colors), static_cast<Shape>(i % shapes)));
    }

    static random_device rd;
    shuffle(weight.begin(), weight.end(), default_random_engine(rd()));
    for (auto j = 2, ii = 0; j < size.first - 2; ++j) {
        for (auto i = 2; i < size.second - 2; ++i, ++ii) {
            map[j][i] = weight[ii];
        }
    }
    return map;
}

void link_link::LinkLink::render(QPainter &qPainter)
{
    //Leave Space for border
    qPainter.save();
    qPainter.translate(1, 1);
    qPainter.translate(1, 1);

    //Draw Diamonds
    {
        qPainter.save();
        for (auto &i: map) {
            qPainter.save();
            for (auto &j: i) {
                j->render(qPainter);
                qPainter.translate(20, 0);
            }
            qPainter.restore();
            qPainter.translate(0, 20);
        }
        qPainter.restore();
    }

    //Draw Players
    {

        for (const auto &player: players) {

            qPainter.save();
            auto position = player->position;
            qPainter.translate(20 * position.second, 20 * position.first);
            player->render(qPainter);
            qPainter.restore();

            //Draw Select Mark
            qPainter.save();
            auto selectedBlock = player->selectedPoint;
            if (selectedBlock != Point{0, 0}) {
                qPainter.translate(20 * selectedBlock.second,
                                   20 * selectedBlock.first);
                player->renderSelectedMark(qPainter);
            }
            qPainter.restore();
        }
    }


    //Draw Paths
    for (const auto &i: linkedPath) {
        qPainter.save();
        qPainter.translate(20 * i.second, 20 * i.first);
        Path().render(qPainter);
        qPainter.restore();
    }


    {

        if (!isHintEnd()) {
            for (const auto &i: hintedPoints) {
                qPainter.save();
                qPainter.translate(20 * i.second, 20 * i.first);
                qPainter.drawLine(QLine(1, 1, 19, 19));
                qPainter.drawLine(QLine(1, 19, 19, 1));
                qPainter.restore();
            }
        }
    }


    //Restore qPainter
    qPainter.restore();
}

void link_link::LinkLink::manipulate(Key key)
{
    if (isGameEnd()) {
        return;
    }
    for (const auto &player: players) {
        auto reactions = player->onManipulated(key);
        for (auto reaction: reactions) {
            handleReaction(reaction, player);
        }
    }
}

void link_link::LinkLink::click(QPointF point)
{
    if (!isFlashing() || isPaused()) {
        return;
    }
    auto position = Point{point.y() / 20, point.x() / 20};
    for (auto i: {0, -1, 1}) {
        auto j = 0;
        auto p = Point{position.first + i, position.second + j};
        if (checkPathable({players[0]->position, p})) {
            players[0]->position = p;
            handleCollidedReaction(players[0], p,
                                   map[p.first][p.second]->onCollided());
            info("LinkLink: Flashing to ({}, {})", p.first, p.second);
            flashing = false;
        }
    }
    for (auto j: {-1, 1}) {
        auto i = 0;
        auto p = Point{position.first + i, position.second + j};
        if (checkPathable({players[0]->position, p})) {
            players[0]->position = p;
            handleCollidedReaction(
              players[0], position,
              map[position.first][position.second]->onCollided());
            info("LinkLink: Flashing to ({}, {})", p.first, p.second);
            flashing = false;
        }
    }
}
void link_link::LinkLink::elapse(uint32_t second)
{
    if (isGameEnd() || isPaused() || !isGameSolvable()) {
        return;
    }

    this->gameTime += second;
}


void link_link::LinkLink::handleReaction(const Reaction &reaction,
                                         PlayerPointer player)
{
    Reactions collidedReactions;
    Point colliding = player->position;
    Point collided;
    int i;
    int j;
    switch (reaction) {
        case Reaction::MoveLeft:
            i = 0;
            j = -1;
            break;
        case Reaction::MoveRight:
            i = 0;
            j = 1;
            break;
        case Reaction::MoveUp:
            i = -1;
            j = 0;
            break;
        case Reaction::MoveDown:
            i = 1;
            j = 0;
            break;
        default:
            return;
    }
    if (player->dizzyedTimeStamp > gameTime) {
        info("LinkLink: manipulation dizzyed");
        i = -i;
        j = -j;
    }
    if (player->freezedTimeStamp > gameTime) {
        info("LinkLink: manipulation freezed");
        i = 0;
        j = 0;
    }
    collided = Point{colliding.first + i, colliding.second + j};
    info("Collision: ({}, {}) with ({}, {})", colliding.first, colliding.second,
         collided.first, collided.second);
    handleCollidedReaction(player, collided,
                           map[collided.first][collided.second]->onCollided());
}

void LinkLink::handleCollidedReaction(PlayerPointer &colliding, Point &collided,
                                      const Reactions &reactions)
{
    for (const auto &reaction: reactions) {
        switch (reaction) {
            case Reaction::Penetrate:
                colliding->position = collided;
                break;
            case Reaction::Select: {
                auto &selectedBlock = colliding->selectedPoint;
                if (collided != selectedBlock &&
                    map[collided.first][collided.second]->id() ==
                      map[selectedBlock.first][selectedBlock.second]->id()) {
                    auto path = genLinkablePath({selectedBlock, collided});
                    if (!path.empty()) {
                        linkedPath = path;
                        map[collided.first][collided.second] =
                          BlockPointer(make_shared<Blank>());
                        map[selectedBlock.first][selectedBlock.second] =
                          BlockPointer(make_shared<Blank>());
                        colliding->score += 1;
                        if (!isHintEnd()) {
                            hintedPoints = findLinkedPair();
                        }
                        selectedBlock = {0, 0};
                        changed = true;
                        break;
                    }
                }
                selectedBlock = collided;
                break;
            }
            case Reaction::ReplaceWithBlank:
                map[collided.first][collided.second] =
                  BlockPointer(make_shared<Blank>());
                changed = true;
                break;
            case Reaction::PlusOneSecond:
                gameEndStamp += 30;
                break;
            case Reaction::Shuffle: {
                for (auto &i: players) {
                    i->position = {1, 1};
                }
                auto size = Point(map.size(), map[0].size());
                Row weight;
                for (auto j = 2, ii = 0; j < size.first - 2; ++j) {
                    for (auto i = 2; i < size.second - 2; ++i, ++ii) {
                        weight.push_back(map[j][i]);
                    }
                }
                static random_device rd;
                shuffle(weight.begin(), weight.end(),
                        default_random_engine(rd()));
                for (auto j = 2, ii = 0; j < size.first - 2; ++j) {
                    for (auto i = 2; i < size.second - 2; ++i, ++ii) {
                        map[j][i] = weight[ii];
                    }
                }

                for (auto &player: players) {
                    player->selectedPoint = {0, 0};
                }

                linkedPath.clear();
                break;
            }
            case Reaction::Hint: {
                hintedPoints = findLinkedPair();
                hintTimeStamp = getGameTime() + 10;
                break;
            }
            case Reaction::StartFlash: {
                flashing = true;
                break;
            }
            case Reaction::Dizzy:
                for (const auto &player: players) {
                    if (player != colliding) {
                        player->dizzyedTimeStamp = gameTime + 10;
                    }
                }
                break;
            case Reaction::Freeze:
                for (const auto &player: players) {
                    if (player != colliding) {
                        player->freezedTimeStamp = gameTime + 10;
                    }
                }
                break;
            default:
                break;
        }
    }
}

// check two block linkable and generate line
Points link_link::LinkLink::genLinkablePath(Line line) const
{

    auto first = line.first;
    auto second = line.second;
    bool find = false;
    Point fV;
    Point sV;
    auto yMax = map.size();
    auto xMax = map[0].size();

    for (int i = 0; i < yMax; ++i) {
        auto lines = vector<Line>{
          {
            {i, first.second},
            {i, second.second},
          },
          {
            {i, first.second},
            {first.first, first.second},
          },
          {
            {i, second.second},
            {second.first, second.second},
          },
        };
        bool valid = true;
        for (const auto &l: lines) {
            if (!checkLinePenetratable(l)) {
                valid = false;
                break;
            }
        }
        if (!map[i][first.second]->penetratable() && first.first != i ||
            !map[i][second.second]->penetratable() && second.first != i) {
            valid = false;
        }
        if (!valid) {
            continue;
        }
        auto ret = Points();
        for (const auto &l: lines) {
            auto penetratableLine = genPenetratableLine(l);
            ret.insert(ret.end(), penetratableLine.begin(),
                       penetratableLine.end());
        }
        return ret;
    }

    for (int j = 0; j < xMax; ++j) {
        auto lines =
          vector<Line>{{{first.first, j}, {second.first, j}},
                       {{first.first, j}, {first.first, first.second}},
                       {{second.first, j}, {second.first, second.second}}};
        bool valid = true;
        for (const auto &l: lines) {
            if (!checkLinePenetratable(l)) {
                valid = false;
                break;
            }
        }
        if (!map[first.first][j]->penetratable() && first.second != j ||
            !map[second.first][j]->penetratable() && second.second != j) {
            valid = false;
        }
        if (!valid) {
            continue;
        }
        auto ret = vector<Point>();
        for (const auto &l: lines) {
            auto penetratableLine = genPenetratableLine(l);
            ret.insert(ret.end(), penetratableLine.begin(),
                       penetratableLine.end());
        }
        return ret;
    }
    return {};
}

// tool function for genLinkablePath
bool link_link::LinkLink::checkLinePenetratable(Line line) const
{

    int *variable = nullptr;
    auto first = line.first;
    auto second = line.second;
    int i = first.first;
    int j = first.second;
    int end = 0;
    Range mm;
    if (first.first == second.first) {
        mm = minmax({first.second, second.second});
        variable = &j;
    } else if (first.second == second.second) {
        mm = minmax({first.first, second.first});
        variable = &i;
    } else {
        return false;
    }

    for (*variable = mm.first + 1; *variable < mm.second; ++*variable) {
        if (!map[i][j]->penetratable()) {
            info("Penetration: Line (({}, {}), ({}, {})) is inpenetratbale, "
                 "because "
                 "({}, {}) is inpenetratable",
                 line.first.first, line.first.second, line.second.first,
                 line.second.second, i, j);
            return false;
        }
    }
    info("Penetration: Line (({}, {}), ({}, {})) is penetratbale",
         line.first.first, line.first.second, line.second.first,
         line.second.second);
    return true;
}

Points link_link::LinkLink::genPenetratableLine(Line line)
{
    auto first = line.first;
    auto second = line.second;
    int *variable = nullptr;
    int i = first.first;
    int j = first.second;
    Range mm;
    if (first.first == second.first) {
        mm = minmax({first.second, second.second});
        variable = &j;
    } else if (first.second == second.second) {
        mm = minmax({first.first, second.first});
        variable = &i;
    } else {
        return {};
    }
    vector<Point> ret;
    for (*variable = mm.first; *variable <= mm.second; ++*variable) {
        ret.emplace_back(i, j);
    }
    return ret;
}

uint64_t link_link::LinkLink::getGameTime() const
{
    return gameTime;
}

uint64_t link_link::LinkLink::getGameTimeLeft() const
{
    return gameEndStamp - gameTime;
}

bool link_link::LinkLink::isGameEnd()
{
    return !isGameSolvable() || gameTime >= gameEndStamp;
}

// Check if the game is still solvable
bool link_link::LinkLink::isGameSolvable()
{
    static bool solvable = true;
    if (changed) {
        changed = false;
        auto row = map.size();
        if (row == 0) {
            return false;
        }
        auto col = map[0].size();
        for (auto i = 1; i < row - 1; ++i) {
            for (auto j = 1; j < col - 1; ++j) {
                for (auto ii = 1; ii < row - 1; ++ii) {
                    for (auto jj = 1; jj < col - 1; ++jj) {
                        auto left = map[i][j];
                        auto right = map[ii][jj];
                        if (left == right) {
                            continue;
                        }
                        if (left->getType() == BlockType::Diamond &&
                            left->id() == right->id()) {
                            if (!genLinkablePath({{i, j}, {ii, jj}}).empty()) {
                                // User can reach the block
                                bool left_reachable = false;
                                auto position = Point{i, j};
                                for (auto iii: {0, -1, 1}) {
                                    auto jjj = 0;
                                    auto p = Point{position.first + iii,
                                                   position.second + jjj};
                                    if (checkPathable({players[0]->position, p})) {
                                        left_reachable = true;
                                    }
                                }
                                for (auto jjj: {-1, 1}) {
                                    auto iii = 0;
                                    auto p = Point{position.first + iii,
                                                   position.second + jjj};
                                    if (checkPathable({players[0]->position, p})) {
                                        left_reachable = true;
                                    }
                                }
                                if (!left_reachable) {
                                    continue;
                                }
                                solvable = true;
                                return true;
                            }
                        } else if (left->getType() == BlockType::Special) {
                            //User can get special block
                            bool left_reachable = false;
                            auto position = Point{i, j};
                            for (auto iii: {0, -1, 1}) {
                                auto jjj = 0;
                                auto p = Point{position.first + iii,
                                               position.second + jjj};
                                if (checkPathable({players[0]->position, p})) {
                                    left_reachable = true;
                                }
                            }
                            for (auto jjj: {-1, 1}) {
                                auto iii = 0;
                                auto p = Point{position.first + iii,
                                               position.second + jjj};
                                if (checkPathable({players[0]->position, p})) {
                                    left_reachable = true;
                                }
                            }
                            if (!left_reachable) {
                                continue;
                            }
                            solvable = true;
                            return true;
                        }
                    }
                }
            }
        }
        solvable = false;
        return false;
    }
    return solvable;
}

bool link_link::LinkLink::isHintEnd() const
{
    return gameTime > hintTimeStamp;
}

uint64_t link_link::LinkLink::getP1Score() const
{
    return players[0]->score;
}

uint64_t link_link::LinkLink::getP2Score() const
{
    return players.size() == 2 ? players[1]->score : 0;
}

static inline bool isDiamond(uint64_t id)
{
    if (id % blockType == static_cast<uint64_t>(BlockType::Diamond)) {
        return true;
    }
    return false;
}

// Check if 2 blocks can be linked
Points link_link::LinkLink::findLinkedPair() const
{

    // From left to right
    for (auto i = 0; i < map.size(); ++i) {
        for (auto j = 0; j < map[0].size(); ++j) {
            if (map[i][j]->id() != static_cast<uint64_t>(BlockType::Blank)) {
                continue;
            }
            std::map<uint64_t, Point> points;
            auto id = map[i][j - 1]->id();
            if (isDiamond(id)) {
                points.insert({id, {i, j - 1}});
            }

            auto k = j;
            for (; map[i][k]->id() == static_cast<uint64_t>(BlockType::Blank);
                 ++k) {
                auto c = i;
                // Go up
                {
                    for (; map[c][k]->id() ==
                           static_cast<uint64_t>(BlockType::Blank);
                         --c) {
                    }
                    auto bid = map[c][k]->id();
                    auto iter = points.find(bid);
                    if (iter != points.end()) {
                        return {iter->second, {c, k}};
                    }
                    if (isDiamond(bid)) {
                        points.insert({bid, {c, k}});
                    }
                }
                // Go down
                {
                    for (c = i; map[c][k]->id() ==
                                static_cast<uint64_t>(BlockType::Blank);
                         ++c) {
                    }
                    auto bid = map[c][k]->id();
                    auto iter = points.find(bid);
                    if (iter != points.end()) {
                        return {iter->second, {c, k}};
                    }
                    if (isDiamond(bid)) {
                        points.insert({bid, {c, k}});
                    }
                }
            }
            id = map[i][k]->id();
            auto iter = points.find(id);
            if (iter != points.end()) {
                return {iter->second, {i, k}};
            }
            j = k;
        }
    }

    //From up to down
    for (auto j = 0; j < map[0].size();) {
        for (auto i = 0; i < map.size(); ++i) {
            if (map[i][j]->id() != static_cast<uint64_t>(BlockType::Blank)) {
                continue;
            }
            std::map<uint64_t, Point> points;
            points.insert({map[i - 1][j]->id(), {i - 1, j}});
            auto k = i;
            for (; map[k][j]->id() == static_cast<uint64_t>(BlockType::Blank);
                 ++k) {
                auto c = i;
                // Go left
                {
                    for (; map[k][c]->id() ==
                           static_cast<uint64_t>(BlockType::Blank);
                         --c) {
                    }
                    auto id = map[k][c]->id();
                    auto iter = points.find(id);
                    if (iter != points.end()) {
                        return {
                          iter->second,
                          {
                            k,
                            c,
                          },
                        };
                    }
                    if (isDiamond(id)) {
                        points.insert({
                          id,
                          {
                            k,
                            c,
                          },
                        });
                    }
                }

                // Go right
                {
                    for (c = i; map[k][c]->id() ==
                                static_cast<uint64_t>(BlockType::Blank);
                         ++c) {
                    }
                    auto id = map[k][c]->id();
                    auto iter = points.find(id);
                    if (iter != points.end()) {
                        return {
                          iter->second,
                          {
                            k,
                            c,
                          },
                        };
                    }
                    if (isDiamond(id)) {
                        points.insert({
                          id,
                          {
                            k,
                            c,
                          },
                        });
                    }
                }
            }
            auto id = map[k][j]->id();
            auto iter = points.find(id);
            if (iter != points.end()) {
                return {
                  iter->second,
                  {
                    k,
                    j,
                  },
                };
            }
            i = k;
        }
    }


    return {};
}

// check if player can reach the block
bool link_link::LinkLink::checkPathable(block::Line line) const
{
    std::list<block::Point> dynamic;
    std::set<block::Point> pathable;
    pathable.insert(line.first);
    dynamic.push_back(line.first);
    while (!dynamic.empty()) {
        const auto start = dynamic.front();
        dynamic.pop_front();
        for (const auto i: {-1, 0, 1}) {
            auto j = 0;
            auto end = Point{start.first + i, start.second + j};
            if (!pathable.count(end) &&
                map[end.first][end.second]->penetratable()) {
                pathable.insert(end);
                dynamic.push_back(end);
                if (end == line.second) {
                    return true;
                }
            }
        }
        for (const auto j: {-1, 0, 1}) {
            auto i = 0;
            auto end = Point{start.first + i, start.second + j};
            if (!pathable.count(end) &&
                map[end.first][end.second]->penetratable()) {
                pathable.insert(end);
                dynamic.push_back(end);
                if (end == line.second) {
                    return true;
                }
            }
        }
    }
    return false;
}
bool link_link::LinkLink::isPaused() const
{
    return paused;
}

bool link_link::LinkLink::isFlashing() const
{
    return flashing;
}

void link_link::LinkLink::togglePaused()
{
    paused = !isPaused();
};

void link_link::LinkLink::reset()
{

    gameTime = 0;
    gameEndStamp = 100;
    hintTimeStamp = 0;
    paused = false;
    players.clear();

    switch (gameType) {
        case link_link::LinkLink::GameType::Single:
            players.push_back(make_shared<Player>(
              Point{1, 1}, PlayerType::Player1, Point{0, 0}));
            break;
        case link_link::LinkLink::GameType::Contest:
            players.push_back(make_shared<Player>(
              Point{1, 1}, PlayerType::Player1, Point{0, 0}));
            players.push_back(make_shared<Player>(
              Point{1, 1}, PlayerType::Player2, Point{0, 0}));
            break;
        default:
            break;
    }

    for (auto &player: players) {
        player->score = 0;
        player->selectedPoint = {
          0,
          0,
        };
        player->position = {
          1,
          1,
        };
    }

    linkedPath.clear();

    map = generateBlocks(
      {
        mapSize[0],
        mapSize[1],

      },
      gameType);
}

void link_link::LinkLink::switchToSingle()
{
    gameType = GameType::Single;
    reset();
}

void link_link::LinkLink::switchToContest()
{
    gameType = GameType::Contest;
    reset();
}

void link_link::LinkLink::save(ostream &out) const
{

    info("LinkLink: Saving Game Archive");

    out << players.size() << ' ';

    out << gameTime << ' ';

    out << gameEndStamp << ' ';
    out << hintTimeStamp << ' ';

    out << isFlashing() << ' ';


    for (const auto &player: players) {
        player->save(out);
    }

    out << map.size() << ' ';
    out << map[0].size() << ' ';

    for (const auto &row: map) {
        for (const auto &block: row) {
            out << block->id() << ' ';
        }
    }
}

void link_link::LinkLink::load(istream &in)
{
    info("LinkLink: Loading Game Archive");

    uint64_t buffer;

    in >> buffer;
    if (buffer == 1) {
        switchToSingle();
    } else {
        switchToContest();
    }

    in >> gameTime;

    in >> gameEndStamp;
    in >> hintTimeStamp;

    in >> flashing;

    paused = true;

    for (auto &player: players) {
        player->load(in);
    }

    in >> buffer;
    map.resize(buffer);

    in >> buffer;
    for (auto &row: map) {
        row.resize(buffer);
    }

    for (auto &row: map) {
        for (auto &block: row) {

            in >> buffer;
            block = generateById(buffer);
        }
    }

    linkedPath.clear();
}
void LinkLink::set_map(block::Map m)
{
    map = std::move(m);
}
