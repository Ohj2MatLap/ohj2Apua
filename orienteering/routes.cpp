#include "routes.hh"

Routes::Routes()
{
}

Routes::~Routes()
{
}

void Routes::set_map_size(int width, int height)
{
   map_width=width;
   map_heigth=height;
}

void Routes::add_point(std::string &name, int x, int y, int height, char marker)
{
    points_by_name[name] = new Point{name,x,y,height,marker};
    std::string coordinate = std::to_string(x)+":"+std::to_string(y);
    points_by_coordinate[coordinate] = new Point{name,x,y,height,marker};
}

bool Routes::connect_route(std::string &from, std::string &to, std::string &route_name)
{
    if(routes_.find(route_name)->first==route_name){
        routes_[route_name].push_back(points_by_name[to]);
        return true;
    }
    else{
        routes_[route_name] = {points_by_name[from],points_by_name[to]};
        return true;
    }
}

void Routes::print_map() const
{
    std::cout<<" ";
    for(int b=0;b<map_width;b++){
        if(b+1>9){
            std::cout<<" ";
            std::cout<<b+1;
        }
        else{
            std::cout<<"  ";
            std::cout<<b+1;
        }
    }
    std::cout<<std::endl;
    for(int i=0;i<map_heigth;i++){
        if(i+1<10){
            std::cout<<" "+std::to_string(i+1);
        }
        else{
            std::cout<<i+1;
        }
        for(int b=0;b<map_width;b++){
            std::cout<<"  ";
            std::string coordinate = std::to_string(b+1)+":"+std::to_string(i+1);
            if(points_by_coordinate.find(coordinate)->first==coordinate){
                std::cout<<points_by_coordinate.find(coordinate)->second->mark;
            }
            else{
                std::cout<<".";
            }
        }
        std::cout<<std::endl;
    }
}

void Routes::print_route_names() const
{
    std::set<std::string> route_names;
    for ( const auto &myPair : routes_ ) {
        route_names.insert(myPair.first);
    }
    std::cout<<"Routes: "<<std::endl;
    for(const auto name : route_names){
        std::cout<<" - "<<name<<std::endl;
    }
}

void Routes::print_points() const
{
    std::map<std::string,char> points_names;
    for ( const auto &myPair : points_by_name ) {
        points_names[myPair.first] = myPair.second->mark;
    }
    std::cout<<"Points:"<<std::endl;
    for(const auto name : points_names){
        std::cout<<" - "<<name.first<<" : "<<name.second<<std::endl;
    }
}

void Routes::print_route(const std::string &name) const
{
    if(name==""){
        std::cout<<"Error: Wrong amount of parameters"<<std::endl;
        return;
    }
    std::vector<std::string> route_point_names;
    bool route_found = false;
    for ( const auto &myPair : routes_ ) {
        if(myPair.first==name){
            route_found=true;
            for(const auto &item : myPair.second)
             route_point_names.push_back(item->name);
        }
    }
    if(route_found==false){
        std::cout<<"Error: Route named "<< name<<" can't be found"<<std::endl;
        return;
    }
    bool first_printed = false;
    for(const auto name : route_point_names){
        if(first_printed==false){
            first_printed = true;
            std::cout<<name<<std::endl;
        }
        else{
            std::cout<<" -> "<<name<<std::endl;
        }
    }
}

void Routes::route_length(const std::string &name) const
{
    if(name==""){
        std::cout<<"Error: Wrong amount of parameters"<<std::endl;
        return;
    }
        double length = 0;//Total length
        double old_x = 0;//Previous x position
        double old_y = 0;//Previous y position
        bool route_found = false;
        for ( const auto &myPair : routes_) {
            if(myPair.first == name){
                route_found = true;
                for ( const auto point_item : myPair.second) {
                    if(old_x==0&&old_y==0){
                        old_x = point_item->x;
                        old_y = point_item->y;
                    }
                    else{
                    length=length+sqrt((old_x-point_item->x)*(old_x-point_item->x)
                            +(old_y-point_item->y)*(old_y-point_item->y));
                    old_x = point_item->x;
                    old_y = point_item->y;
                    }
                }
            }
        }
        if(route_found==false){
            std::cout<<"Error: Route named "<< name<<" can't be found"<<std::endl;
            return;
        }
        std::cout<<"Route "<<name<<" length was "<<std::setprecision(2)<<length<<std::endl;
}

void Routes::greatest_rise(const std::string &point_name) const
{
    int greatest_rise = -1;//Greatest heigth difference between points
    int old_heigth = 0;//Previous points heigth
    int rise = 0;//Heigth difference between points
    std::set<std::string> route_names;//Includes route names that have equal greatest_rise
    bool point_name_found = false;
    bool route_found = false;

    for(auto route : routes_){
        point_name_found = false;
        for(auto points : route.second){
            if(points->name==point_name || point_name_found){
                route_found = true;
                if(point_name_found==false){
                    old_heigth=points->heigth;
                    point_name_found = true;
                }
                else{
                    if(old_heigth-points->heigth<=0){
                        rise = rise-old_heigth+points->heigth;
                        old_heigth=points->heigth;
                    }
                    else{
                        if(greatest_rise<rise){
                           greatest_rise=rise;
                           route_names = {route.first};
                           rise=0;
                        }
                        else if(greatest_rise==rise){
                            route_names.insert(route.first);
                            rise=0;
                        }
                        else{rise=0;}
                        break;
                    }
                }
            }
        }
    }
    if(route_found==false){
        std::cout<<"Error: Point named "<<point_name<<" can't be found"<<std::endl;
    }
    else if(greatest_rise<=0){
        std::cout<<"No route rises after point "<<point_name<<std::endl;
    }
    else{
        std::cout<<"Greatest rise after point "<<point_name<<", "<<greatest_rise<<" meters, is on route(s):"<<std::endl;
        for(const auto route_name : route_names){
             std::cout<<" - "<<route_name<<std::endl;
        }
    }
}

