#include <cstdlib>  
#include <iostream>
#include <fstream>
#include <osmium/io/any_input.hpp>
#include <osmium/io/any_compression.hpp>
#include <osmium/io/input_iterator.hpp>
#include <osmium/io/output_iterator.hpp>


void catch_interrupt(int sig) {
  std::cerr << "Interrupting...\n";
  std::exit(1);
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " OSMFILE OSMTAB\n";
        std::exit(1);
    }

    signal(SIGINT, catch_interrupt);

    osmium::io::File input_file{argv[1]};
    osmium::io::Reader reader{input_file, osmium::osm_entity_bits::changeset};

    std::ofstream myfile;
    myfile.open(argv[2]);
    myfile << "id\tcreated_at\tnum_changes\tnum_comments\tmin_lon\tmin_lat\tmax_lon\tmax_lat" << '\n';

    auto input_range = osmium::io::make_input_iterator_range<osmium::Changeset>(reader);
   
    for (const auto& changeset : input_range) {

        if ( changeset.bounds().valid() && 
             changeset.created_at().valid() && 
             changeset.bounds().bottom_left().valid() && 
             changeset.bounds().top_right().valid()) {
            myfile << changeset.id() << '\t';
            myfile << changeset.created_at().seconds_since_epoch() << '\t';
            myfile << changeset.num_changes() << '\t';
            myfile << changeset.num_comments() << '\t';
            myfile << changeset.bounds().bottom_left().lon() << '\t';
            myfile << changeset.bounds().bottom_left().lat() << '\t';
            myfile << changeset.bounds().top_right().lon() << '\t';
            myfile << changeset.bounds().top_right().lat() << '\n';
        }

    }

    reader.close();
   
    myfile.close();


}
