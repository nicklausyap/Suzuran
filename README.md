# Suzuran

Suzuran is a file format that can be used to store data record and the data types. This open source file format is an experimental project.
Below is a look at the Suzuran specification:

## Suzuran Specification

## Types

Following are the types are available (to be updated)
* **int**: represent integer
* **string**: represent string

## Explanation

```
\1
int Index
string Organization_Id
string Name
string website
string Country
string Description
int Founded
string Industry
int Number of employees
<1>
<data>
1
FAB0d41d5b5d22c
Ferrell LLC
"https://price.net/"
Papua New Guinea
Horizontal empowering knowledgebase
1990
Plastics
3290
</data>
<data>
2
6A7EdDEA9FaDC52
"Mckinney, Riley and Day"
"http://www.hall-buchanan.info/"
Finland
User-centric system-worthy leverage
2013
"Glass / Ceramics / Concrete"
4900
</data>
</1>
```

\1 meaning the depth is 1. This has to be on the first line
```
\1
```
Below is representing the structure of the data and their type at depth 1.
int Index meaning the data Index is of type integer.
string Organization Id meaning the data Organization_Id is of string type.
```
int Index
string Organization_Id
string Name
string website
string Country
string Description
int Founded
string Industry
int Number of employees
```
This is the boundary of depth 1. Consider <1> is starting boundary and </1> as end of the boundary depth
```
<1>
</1>
```
Each data record is enclosed within data opening and closing tag. Each data value has to be on a newline. The data value would be check against the data type declare in the structure only if mandatory. The ordering of the data value has to be follow same in the structure
```
<data>
1
FAB0d41d5b5d22c
Ferrell LLC
"https://price.net/"
Papua New Guinea
Horizontal empowering knowledgebase
1990
Plastics
3290
</data>
```

Here we can see there is two data record at depth 1
```
<1>
<data>
1
FAB0d41d5b5d22c
Ferrell LLC
"https://price.net/"
Papua New Guinea
Horizontal empowering knowledgebase
1990
Plastics
3290
</data>
<data>
2
6A7EdDEA9FaDC52
"Mckinney, Riley and Day"
"http://www.hall-buchanan.info/"
Finland
User-centric system-worthy leverage
2013
"Glass / Ceramics / Concrete"
4900
</data>
</1>
```
## Final Note
The data used in the explanation is for example purpose only. The data is not real data and does not represent any entity. So rest assured privacy is maintained

## Progress
* Finalize the file format specification (OTW)
* Create a parser for Suzuran (OTW)
