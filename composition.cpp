#include "composition.h"

#include <QXmlStreamWriter>
#include <QtXmlPatterns>
#include <QMessageBox>


Composition::Composition(fsmVector fsms, linkVector links)
     : fsms_(fsms), links_(links)
{

}

fsmVector Composition::getFsms() const
{
     return fsms_;
}

linkVector Composition::getLinks() const
{
     return links_;
}

void Composition::formBalm2Script() const
{
     fsmVector myFSMs = getFsms();
     if (myFSMs.size() != 2)
     {
          qDebug() << "we need 2 components...";
          return;
     }

     QFile script("script.sh");
     if (!script.open(QIODevice::WriteOnly))
     {
          return;
     }
     QTextStream toScript(&script);

     QString name1 = myFSMs[0].getId() + ".aut";
     QString name2 = myFSMs[1].getId() + ".aut";

     linkVector myLinks = getLinks();

     QString channels1_inp = "", channels1_out = "", channels2_inp = "", channels2_out = "", ext_channel1 = "", ext_channel2 = "";
     int E_number=0;
     for (size_t i = 0; i < myLinks.size(); i++)
     {
          if (myLinks[i].getInputFsm().getId() == myFSMs[0].getId())
          {
               channels1_inp += myLinks[i].getId();
               channels1_inp += '|';
               if ( myLinks[i].getOutputFsm().getId()=="" )
               {
                    ext_channel2 += "E" + QString::number(E_number)+',';
               }
               E_number++;
          }

          if ( myLinks[i].getOutputFsm().getId() == myFSMs[0].getId() )
          {
               channels1_out += myLinks[i].getId();
               channels1_out += '|';
               if ( myLinks[i].getInputFsm().getId() == "" )
               {
                    ext_channel2 += "E" + QString::number(E_number) + ',';
               }
               E_number++;
          }

          if ( myLinks[i].getInputFsm().getId() == myFSMs[1].getId() )
          {
               channels2_inp += myLinks[i].getId();
               channels2_inp += '|';
               if ( myLinks[i].getOutputFsm().getId() == "" )
               {
                    ext_channel1 += "E" + QString::number(E_number) + ',';
               }
               E_number++;
          }

          if (myLinks[i].getOutputFsm().getId() == myFSMs[1].getId())
          {
               channels2_out += myLinks[i].getId();
               channels2_out += '|';
               if (myLinks[i].getInputFsm().getId()=="")
               {
                    ext_channel1 += "E" + QString::number(E_number) + ',';
               }
               E_number++;
          }
     }

     channels1_out.remove(channels1_out.size() - 1, 1);
     channels2_out.remove(channels2_out.size() - 1, 1);
     ext_channel1.remove(ext_channel1.size() - 1, 1);
     ext_channel2.remove(ext_channel2.size() - 1, 1);

     QString chan_inp = channels1_inp+ext_channel1;
     QString chan_out = channels1_out+ext_channel2;

     const static QString balm("balm -c ");
     const static QString quote("\"");
     QString read_para1 = balm + quote + "read_para_fsm " + channels1_inp + channels1_out + " " + name1 + " poly" + name1 + quote;
     QString read_para2 = balm + quote + "read_para_fsm " + channels2_inp + channels2_out + " " + name2 + " poly" + name2+ quote;
     QString chan_sync = balm + quote + "chan_sync " + channels1_inp + channels1_out + "|E " + channels2_inp + channels2_out+ "|E  poly" + name1 + " poly" + name2 + " sync" + name1 + " sync" + name2+ quote;
     QString expansion = balm + quote + "expansion " + ext_channel1 + "," + ext_channel2 + name2 + " exp" + name2 + quote;
     QString product = balm + quote + "product poly" + name1 + " exp" + name2 + " pro.aut" + quote;
     QString restriction = balm + quote + "restriction " + ext_channel1 + "," + ext_channel2 + " pro.aut" + " restr.aut" + quote;
     QString support = balm + quote + "support " + chan_inp + ","+ chan_out + ",E("+ QString::number(E_number) + ") restr.aut supp.aut" + quote;
     QString write_para = balm + quote + "write_para_fsm " + channels1_inp + channels1_out + "|E ext_channel1|ext_channel2 supp.aut fsm.aut" + quote;

     toScript << read_para1 << "\n" << read_para2 << "\n" << chan_sync << "\n" <<
                 expansion << "\n" << product << "\n" << restriction << "\n" <<
                 support << "\n" << write_para;
}

void Composition::formXmlFile() const
{
     QFile xmlCompositionFile("composition.xml");
     xmlCompositionFile.open(QIODevice::WriteOnly);

     QXmlStreamWriter xmlWriter(&xmlCompositionFile);
     xmlWriter.setAutoFormatting(true);
     xmlWriter.writeStartDocument();

     auto isExternal = [](const Fsm& fsm)
     {
          return ( ( "" == fsm.getId() ) && ( "" == fsm.getName() ) );
     };

     auto writeFsmInfo = [&xmlWriter, &isExternal](const Fsm& fsm)
     {
          if(isExternal(fsm))
          {
               xmlWriter.writeAttribute("type", "external");
          }
          else
          {
               xmlWriter.writeAttribute("type", "internal");
               xmlWriter.writeAttribute("id_comp", fsm.getId());
          }
     };

     xmlWriter.writeStartElement("start");

     xmlWriter.writeStartElement("composition"); // <composition>
     for(const auto& fsm : fsms_)
     {
          xmlWriter.writeStartElement("FSM");
          xmlWriter.writeAttribute("name", fsm.getName());
          xmlWriter.writeAttribute("id", fsm.getId());
          xmlWriter.writeEndElement(); //</FSM>
     }
     xmlWriter.writeEndElement(); // </composition>

     xmlWriter.writeStartElement("channels");
     xmlWriter.writeAttribute("num", QString::number(links_.size()));
     for(const auto& link : links_)
     {
          xmlWriter.writeStartElement("channel"); // <channel>
          xmlWriter.writeAttribute("id", link.getId());

          xmlWriter.writeStartElement("input");
          Fsm inputFsm = link.getInputFsm();
          writeFsmInfo(inputFsm);
          xmlWriter.writeEndElement(); // </input>

          xmlWriter.writeStartElement("output");
          Fsm outputFsm = link.getOutputFsm();
          writeFsmInfo(outputFsm);
          xmlWriter.writeEndElement();

          xmlWriter.writeEndElement(); // </channel>
     }
     xmlWriter.writeEndElement();// </channels>

     xmlWriter.writeEndElement();// </start>

     xmlWriter.writeEndDocument();// XML END
     xmlCompositionFile.close();
}


