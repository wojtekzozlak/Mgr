#ifndef _SCHEMA_
#define _SCHEMA_

#include <set>
#include <string>

supersonic::TupleSchema lineitem_schema() {
  supersonic::TupleSchema tuple_schema;
  tuple_schema.add_attribute(supersonic::Attribute("L_ORDERKEY",
                                                   supersonic::INT32,
                                                   supersonic::NOT_NULLABLE));
  tuple_schema.add_attribute(supersonic::Attribute("L_PARTKEY",
                                                   supersonic::INT32,
                                                   supersonic::NOT_NULLABLE));
  tuple_schema.add_attribute(supersonic::Attribute("L_SUPPKEY",
                                                   supersonic::INT32,
                                                   supersonic::NOT_NULLABLE));
  tuple_schema.add_attribute(supersonic::Attribute("L_LINENUMBER",
                                                   supersonic::INT32,
                                                   supersonic::NOT_NULLABLE));
  tuple_schema.add_attribute(supersonic::Attribute("L_QUANTITY",
                                                   supersonic::FLOAT,
                                                   supersonic::NOT_NULLABLE));
  tuple_schema.add_attribute(supersonic::Attribute("L_EXTENDEDPRICE",
                                                   supersonic::FLOAT,
                                                   supersonic::NOT_NULLABLE));
  tuple_schema.add_attribute(supersonic::Attribute("L_DISCOUNT",
                                                   supersonic::FLOAT,
                                                   supersonic::NOT_NULLABLE));
  tuple_schema.add_attribute(supersonic::Attribute("L_TAX",
                                                   supersonic::FLOAT,
                                                   supersonic::NOT_NULLABLE));
  tuple_schema.add_attribute(supersonic::Attribute("L_RETURNFLAG",
                                                   supersonic::STRING,
                                                   supersonic::NOT_NULLABLE));
  tuple_schema.add_attribute(supersonic::Attribute("L_LINESTATUS",
                                                   supersonic::STRING,
                                                   supersonic::NOT_NULLABLE));
  tuple_schema.add_attribute(supersonic::Attribute("L_SHIPDATE",
                                                   supersonic::DATE,
                                                   supersonic::NOT_NULLABLE));
  tuple_schema.add_attribute(supersonic::Attribute("L_COMMITDATE",
                                                   supersonic::DATE,
                                                   supersonic::NOT_NULLABLE));
  tuple_schema.add_attribute(supersonic::Attribute("L_RECEIPTDATE",
                                                   supersonic::DATE,
                                                   supersonic::NOT_NULLABLE));
  tuple_schema.add_attribute(supersonic::Attribute("L_SHIPINSTRUCT",
                                                   supersonic::STRING,
                                                   supersonic::NOT_NULLABLE));
  tuple_schema.add_attribute(supersonic::Attribute("L_SHIPMODE",
                                                   supersonic::STRING,
                                                   supersonic::NOT_NULLABLE));
  tuple_schema.add_attribute(supersonic::Attribute("L_COMMENT",
                                                   supersonic::STRING,
                                                   supersonic::NOT_NULLABLE));
  return tuple_schema;
}


supersonic::TupleSchema subset_schema(const std::set<std::string>& names) {
  supersonic::TupleSchema all = lineitem_schema();
  supersonic::TupleSchema subset;

  for (int i = 0; i < all.attribute_count(); i++) {
    supersonic::Attribute attr = all.attribute(i);
    if (names.find(attr.name()) != names.end()) {
      subset.add_attribute(attr);
    }
  }

  return subset;
}


supersonic::TupleSchema Q1() {
  std::set<std::string> attrs;
  attrs.insert("L_RETURNFLAG");
  attrs.insert("L_LINESTATUS");
  attrs.insert("L_QUANTITY");
  attrs.insert("L_EXTENDEDPRICE");
  attrs.insert("L_DISCOUNT");
  attrs.insert("L_TAX");
  attrs.insert("L_SHIPDATE");
  supersonic::TupleSchema result = subset_schema(attrs);
  CHECK_EQ(attrs.size(), result.attribute_count());
  return result;
}

supersonic::TupleSchema Q2() {
  std::set<std::string> attrs;
  attrs.insert("L_QUANTITY");
  attrs.insert("L_EXTENDEDPRICE");
  attrs.insert("L_DISCOUNT");
  attrs.insert("L_SHIPDATE");
  supersonic::TupleSchema result = subset_schema(attrs);
  CHECK_EQ(attrs.size(), result.attribute_count());
  return result;
}

supersonic::TupleSchema Q3() {
  std::set<std::string> attrs;
  attrs.insert("L_ORDERKEY");
  attrs.insert("L_EXTENDEDPRICE");
  attrs.insert("L_DISCOUNT");
  attrs.insert("L_SHIPDATE");
  supersonic::TupleSchema result = subset_schema(attrs);
  CHECK_EQ(attrs.size(), result.attribute_count());
  return result;
}

supersonic::TupleSchema Q4() {
  return lineitem_schema();
}

supersonic::TupleSchema Q5() {
  std::set<std::string> attrs;
  attrs.insert("L_EXTENDEDPRICE");
  attrs.insert("L_ORDERKEY");
  attrs.insert("L_DISCOUNT");
  attrs.insert("L_SUPPKEY");
  supersonic::TupleSchema result = subset_schema(attrs);
  CHECK_EQ(attrs.size(), result.attribute_count());
  return result;
}

supersonic::TupleSchema Q6() {
  std::set<std::string> attrs;
  attrs.insert("L_EXTENDEDPRICE");
  attrs.insert("L_DISCOUNT");
  attrs.insert("L_SHIPDATE");
  attrs.insert("L_QUANTITY");
  supersonic::TupleSchema result = subset_schema(attrs);
  CHECK_EQ(attrs.size(), result.attribute_count());
  return result;
}

supersonic::TupleSchema Q7() {
  std::set<std::string> attrs;
  attrs.insert("L_EXTENDEDPRICE");
  attrs.insert("L_DISCOUNT");
  attrs.insert("L_ORDERKEY");
  attrs.insert("L_SUPPKEY");
  attrs.insert("L_SHIPDATE");
  supersonic::TupleSchema result = subset_schema(attrs);
  CHECK_EQ(attrs.size(), result.attribute_count());
  return result;
}

supersonic::TupleSchema Q8() {
  std::set<std::string> attrs;
  attrs.insert("L_EXTENDEDPRICE");
  attrs.insert("L_DISCOUNT");
  attrs.insert("L_ORDERKEY");
  attrs.insert("L_SUPPKEY");
  attrs.insert("L_PARTKEY");
  supersonic::TupleSchema result = subset_schema(attrs);
  CHECK_EQ(attrs.size(), result.attribute_count());
  return result;
}

supersonic::TupleSchema Q9() {
  std::set<std::string> attrs;
  attrs.insert("L_EXTENDEDPRICE");
  attrs.insert("L_DISCOUNT");
  attrs.insert("L_QUANTITY");
  supersonic::TupleSchema result = subset_schema(attrs);
  CHECK_EQ(attrs.size(), result.attribute_count());
  return result;
}

supersonic::TupleSchema Q10() {
  std::set<std::string> attrs;
  attrs.insert("L_EXTENDEDPRICE");
  attrs.insert("L_DISCOUNT");
  attrs.insert("L_ORDERKEY");
  attrs.insert("L_RETURNFLAG");
  supersonic::TupleSchema result = subset_schema(attrs);
  CHECK_EQ(attrs.size(), result.attribute_count());
  return result;
}

supersonic::TupleSchema Q12() {
  std::set<std::string> attrs;
  attrs.insert("L_SHIPMODE");
  attrs.insert("L_ORDERKEY");
  attrs.insert("L_COMMITDATE");
  attrs.insert("L_RECEIPTDATE");
  supersonic::TupleSchema result = subset_schema(attrs);
  CHECK_EQ(attrs.size(), result.attribute_count());
  return result;
}

supersonic::TupleSchema Q14() {
  std::set<std::string> attrs;
  attrs.insert("L_EXTENDEDPRICE");
  attrs.insert("L_DISCOUNT");
  attrs.insert("L_PARTKEY");
  supersonic::TupleSchema result = subset_schema(attrs);
  CHECK_EQ(attrs.size(), result.attribute_count());
  return result;
}

supersonic::TupleSchema Q15() {
  std::set<std::string> attrs;
  attrs.insert("L_SUPPKEY");
  attrs.insert("L_EXTENDEDPRICE");
  attrs.insert("L_DISCOUNT");
  supersonic::TupleSchema result = subset_schema(attrs);
  CHECK_EQ(attrs.size(), result.attribute_count());
  return result;
}

supersonic::TupleSchema Q17() {
  std::set<std::string> attrs;
  attrs.insert("L_EXTENDEDPRICE");
  attrs.insert("L_PARTKEY");
  attrs.insert("L_QUANTITY");
  supersonic::TupleSchema result = subset_schema(attrs);
  CHECK_EQ(attrs.size(), result.attribute_count());
  return result;
}

supersonic::TupleSchema Q18() {
  std::set<std::string> attrs;
  attrs.insert("L_QUANTITY");
  attrs.insert("L_ORDERKEY");
  supersonic::TupleSchema result = subset_schema(attrs);
  CHECK_EQ(attrs.size(), result.attribute_count());
  return result;
}

supersonic::TupleSchema Q19() {
  std::set<std::string> attrs;
  attrs.insert("L_EXTENDEDPRICE");
  attrs.insert("L_DISCOUNT");
  attrs.insert("L_PARTKEY");
  attrs.insert("L_SHIPMODE");
  attrs.insert("L_SHIPINSTRUCT");
  attrs.insert("L_QUANTITY");
  supersonic::TupleSchema result = subset_schema(attrs);
  CHECK_EQ(attrs.size(), result.attribute_count());
  return result;
}

supersonic::TupleSchema Q20() {
  std::set<std::string> attrs;
  attrs.insert("L_PARTKEY");
  attrs.insert("L_QUANTITY");
  attrs.insert("L_SUPPKEY");
  attrs.insert("L_SHIPDATE");
  supersonic::TupleSchema result = subset_schema(attrs);
  CHECK_EQ(attrs.size(), result.attribute_count());
  return result;
}

#endif  // _SCHEMA_
