#ifndef BDT2_BASIC_DEFS_HPP
#define BDT2_BASIC_DEFS_HPP



namespace boost { 
  namespace date_time2 {

    /// Enum of the gregorian weekdays for construction purposes.
    enum weekdays { Sun, Mon, Tue, Wed, Thu, Fri, Sat};

    /// Used to specify the week of a month -- Fifth is same as last if only 4
    enum month_weeks { First=1, Second, Third, Fourth, Fifth, Last=5 };

    /// Used to handle the case of "Sunday nearest 1/1/2010" -- todo hate the name
    enum direction_type { Before, After, Nearest };

    /// Some enums for the months -- todo hate the name, maybe strong enum
    enum greg_months { Jan=1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };

    /// Defines the possible order in which Month, Day, & Year will appear in a date string
    enum class ymd_order_spec {ymd_order_iso,  ///<order is year-month-day
	                       ymd_order_dmy,  ///<day-month-year
	                       ymd_order_us};  ///<order is month-day-year


    /// For formatting dates and times into iso format
    enum class iso_formats { normal, extended };

    //rejected approach...
    // template<typename CharT>
    // struct gregorian_month_names_struct
    // {
    //   typedef CharT char_type;
    //   const   CharT* jan_short;
    //   const   CharT* feb_short;
    //   const   CharT* mar_short;
    //   const   CharT* apr_short;
    //   const   CharT* may_short;
    //   const   CharT* jun_short;
    //   const   CharT* jul_short;
    //   const   CharT* aug_short;
    //   const   CharT* sep_short;
    //   const   CharT* oct_short;
    //   const   CharT* nov_short;
    //   const   CharT* dec_short;
    // };

    /// Array used to hold character strings for i/o purposes
    template<typename CharT, std::size_t max_name>
    struct gregorian_month_names_array
    {
      std::array<std::array<CharT, max_name+1>, 12> names; //longest name is max_name chars + string end
    };

    /// An array of the short month names -- todo, make sure this has internal linkage in c++11
    gregorian_month_names_array<char, 3> short_month_names 
                             = { "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };

    /// An array of the long month names -- todo, make sure this has internal linkage
    gregorian_month_names_array<char, 9> long_month_names 
    = { "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december" };


  } //namespace date_time2
} //namespace boost

#endif
