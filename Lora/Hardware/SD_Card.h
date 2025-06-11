#ifndef __SD_Card_h
#define __SD_Card_h
#define CT_SDSC   0x01   // 标准容量 SD (v1.x)
#define CT_SDHC   0x02   // 高容量 SDHC/SDXC (v2)
#define CMD0   0   /* GO_IDLE_STATE           */
#define CMD1   1   /* SEND_OP_COND  (MMC)     */
#define CMD2   2   /* ALL_SEND_CID   (SD)     */
#define CMD3   3   /* SEND_REL_ADDR  (SD)     */
#define CMD4   4   /* SET_DSR                 */
#define CMD6   6   /* SWITCH_FUNC / MMC_SWITCH*/
#define CMD7   7   /* SELECT/DESELECT_CARD    */
#define CMD8   8   /* SEND_IF_COND            */
#define CMD9   9   /* SEND_CSD                */
#define CMD10 10   /* SEND_CID                */
#define CMD12 12   /* STOP_TRANSMISSION       */
#define CMD13 13   /* SEND_STATUS            */
#define CMD16 16   /* SET_BLOCKLEN            */
#define CMD17 17   /* READ_SINGLE_BLOCK       */
#define CMD18 18   /* READ_MULTIPLE_BLOCK     */
#define CMD23 23   /* SET_BLOCK_COUNT (MMC)   */
#define CMD24 24   /* WRITE_BLOCK             */
#define CMD25 25   /* WRITE_MULTIPLE_BLOCK    */
#define CMD27 27   /* PROGRAM_CSD             */
#define CMD28 28   /* SET_WRITE_PROT          */
#define CMD29 29   /* CLR_WRITE_PROT          */
#define CMD32 32   /* ERASE_WR_BLK_START      */
#define CMD33 33   /* ERASE_WR_BLK_END        */
#define CMD38 38   /* ERASE                   */
#define CMD55 55   /* APP_CMD (前导 ACMD)     */
#define CMD56 56   /* GEN_CMD                 */
#define CMD58 58   /* READ_OCR                */
#define CMD59 59   /* CRC_ON_OFF              */

#define Creat_New_File 1
#define Append_In_File 2

uint8_t SD_Initialize(void);

uint8_t SD_SendCommand(uint8_t cmd, uint32_t arg, uint8_t crc);
uint8_t SD_Check(void);
uint8_t SD_Initialize(void);
uint8_t SD_WriteSector(uint32_t sectorAddr, uint8_t *data);
uint8_t SD_ReadSector(uint32_t sectorAddr, uint8_t *buffer);

#endif



